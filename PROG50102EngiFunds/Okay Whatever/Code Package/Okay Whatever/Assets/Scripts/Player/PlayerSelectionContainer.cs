using System.Collections.Generic;
using UnityEngine;

public class PlayerSelectionContainer : MonoBehaviour
{
    private List<GameObject> _players;
    private int _currentPlayerIndex;

    private void Start()
    {
        IsSelectSpawnPoint spawnPoint = GetComponentInChildren<IsSelectSpawnPoint>();
        if (spawnPoint != null)
        {
            _currentPlayerIndex = PlayerManager.Instance.ActivePlayerIndex;
            _players = new List<GameObject>();
            PlayerManager.Instance.InstantiateAllPlayers(ref _players, spawnPoint.transform);
            SetActivePlayer(true);
        }
        else
        {
            Debug.LogError("Cannot find required 'IsSelectSpawnPoint'. Forced return to main menu");
            LevelManager.Instance.UnloadCurrentLevel();
        }
    }

    public void NextPlayer()
    {
        SetActivePlayer(false);
        _currentPlayerIndex = PlayerManager.Instance.NextActivePlayer();
        SetActivePlayer(true);
    }

    public void PrevPlayer()
    {
        SetActivePlayer(false);
        _currentPlayerIndex = PlayerManager.Instance.PrevActivePlayer();
        SetActivePlayer(true);
    }

    public void SelectPlayer()
    {
        GameStateManager.Instance.SetTrigger(GameStateManager.mainMenu);
    }

    public void SetActivePlayer(bool value)
    {
        if (_currentPlayerIndex < 0 || _currentPlayerIndex >= _players.Count)
        {
            Debug.LogError("PlayerSelectionContainer::NextPlaer() used invalid index");
            return;
        }
        _players[_currentPlayerIndex].gameObject.SetActive(value);
    }
}
