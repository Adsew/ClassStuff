using System.Collections.Generic;
using UnityEngine;

public class PlayerManager : MonoBehaviour
{
    private static PlayerManager _instance;
    public static PlayerManager Instance
    {
        get { return _instance; }
    }

    [SerializeField]
    private List<GameObject> _players = new List<GameObject>();
    private int _activePlayerIndex;
    public int ActivePlayerIndex
    {
        get { return _activePlayerIndex; }
    }

    public string playerAssetBundleName;

    public GameObject playerShell;
    public GameObject activePlayer;

    public IsSpawnPoint playerStart;

    public HealthText healthText;

    private void Awake()
    {
        if (_instance == null)
        {
            _instance = this;
        }
        else
        {
            Destroy(this);
        }
    }

    // Use this for initialization
    void Start()
    {
        _activePlayerIndex = 0;
        LoadCharacters();
    }

    private void LoadCharacters()
    {
        _players.Clear();
        List<Object> loadedObjects = BundleManager.Instance.LoadObjectsFromFile(playerAssetBundleName);
        foreach (Object obj in loadedObjects)
        {
            GameObject gameObject = (GameObject)obj;
            gameObject.SetActive(false);
            _players.Add(gameObject);
        }
    }

    public int NextActivePlayer()
    {
        _activePlayerIndex = (_activePlayerIndex + 1) % _players.Count;
        return _activePlayerIndex;
    }

    public int PrevActivePlayer()
    {
        _activePlayerIndex--;
        if (_activePlayerIndex < 0) { _activePlayerIndex = _players.Count - 1; }
        return _activePlayerIndex;
    }

    public void InstantiateAllPlayers(ref List<GameObject> playerList, Transform t)
    {
        playerList.Clear();
        foreach (GameObject player in _players)
        {
            playerList.Add(Instantiate(player, t));
        }
    }

    public GameObject InstantiateActivePlayer(Transform t)
    {
        Debug.Assert(activePlayer == null, "PlayerManager cannot instantiate player when there is already an active player");
        if (activePlayer == null && _activePlayerIndex >= 0 && _activePlayerIndex < _players.Count)
        {
            GameObject gObject = Instantiate(playerShell);
            gObject.transform.parent = null;
            gObject.transform.position = t.transform.position;
            gObject.transform.rotation = t.transform.rotation;

            GameObject playerObject = Instantiate(_players[_activePlayerIndex]);
            playerObject.transform.position = gObject.transform.position;
            playerObject.transform.parent = gObject.transform;

            gObject.SetActive(true);
            playerObject.SetActive(true);

            activePlayer = gObject;
            return gObject;
        }
        return null;
    }

    public void DestroyActivePlayer()
    {
        if (activePlayer != null)
        {
            Destroy(activePlayer);
        }
    }

    public void PlayerDied()
    {
        if (activePlayer != null)
        {
            PlayerMovement playerMovement = activePlayer.GetComponent<PlayerMovement>();
            if (playerMovement != null)
            {
                playerMovement.setMovementLock(true);
            }

            IsPlayer player = activePlayer.GetComponent<IsPlayer>();
            if (player != null)
            {
                if (player.lives > 0)
                {
                    GameStateManager.Instance.SetTrigger(GameStateManager.playerDied);
                }
                else
                {
                    GameStateManager.Instance.SetTrigger(GameStateManager.gameOver);
                }
                UpdateUIPlayerLives(player.lives);
            }
        }
        else
        {
            Debug.LogError("PlayerDied() cannot find active player");
        }
    }

    public void ReviveActivePlayer()
    {
        if (activePlayer != null)
        {
            IsPlayer player = activePlayer.GetComponent<IsPlayer>();
            if (player != null && player.isDead)
            {
                player.Revive();
                if (playerStart != null)
                {
                    player.transform.position = playerStart.transform.position;
                    player.transform.forward = playerStart.transform.forward;
                }


            }

        }
        else
        {
            Debug.LogError("ReviveActivePlayer() cannot find active player");
        }
    }

    public void UpdateUIPlayerLives(int count)
    {
        if (healthText != null)
        {
            healthText.UpdateHealth(count);
        }
    }
}
