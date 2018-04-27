using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class NetworkSpawner : Photon.PunBehaviour
{
    public GameObject Player { get; private set; }
    public Text HealthText;
    [SerializeField]
    private List<Transform> _startPositions = new List<Transform>();
    [SerializeField]
    private List<EnemySpawnPoint> _enemySpawns = new List<EnemySpawnPoint>();
    [SerializeField]
    private Track _startTrack;

    private void Start()
    {
        LobbyManager.Instance.NetworkSpawner = this;
    }

    private void OnDestroy()
    {
        // eventually move this call out to a GameManager
        LobbyManager.Instance.EndGame();
    }

    public void Spawn()
    {
        Debug.Assert(_startPositions.Count == 2, "There should only ever be 2 spawn positions");
        if (_startPositions.Count != 2) return;
        // select spawn point based on who is the master
        var spawnTrans = PhotonNetwork.isMasterClient ? _startPositions[0] : _startPositions[1];

        // grab the current selected character
        Character character = LobbyManager.Instance.SelectedCharacter;
        if (character == null)
        {
            throw new System.NullReferenceException("Cannot spawn player without a valid player to spawn.");
        }
        // spawn the new player
        Player = PhotonNetwork.Instantiate(character.prefabLocation, spawnTrans.position, spawnTrans.rotation, 0);
        var movement = Player.GetComponent<PlayerMovement>();
        Debug.Assert(_startTrack != null, "NetworSpawner requires a starting track");
        movement.currentTrack = _startTrack;
        var gameCharacter = Player.GetComponent<GameCharacter>();
        Debug.Assert(_startTrack != null, "NetworkSpawner requires a game character");
        gameCharacter.HealthText = HealthText;

        if (PhotonNetwork.isMasterClient)
        {
            foreach (EnemySpawnPoint e in _enemySpawns)
            {
                e.Spawn();
            }
        }
    }

#if UNITY_EDITOR
    Color gizmoColor = Color.green;
    float radius = 0.5f;
    private void OnDrawGizmos()
    {
        Gizmos.color = gizmoColor;
        foreach (var trans in _startPositions)
        {
            if (trans != null)
            {
                Gizmos.DrawSphere(trans.position, radius);
            }
        }
    }
#endif
}