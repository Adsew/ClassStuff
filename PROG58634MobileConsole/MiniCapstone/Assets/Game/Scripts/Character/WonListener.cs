using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WonListener : Photon.PunBehaviour {
    public string WonMenu;

    EventBehaviour _eventBehaviour;

    private void Start()
    {
        _eventBehaviour = GetComponent<EventBehaviour>();
    }

    private void OnEnable()
    {
        if (_eventBehaviour == null)
        {
            _eventBehaviour = GetComponent<EventBehaviour>();
        }

        if (_eventBehaviour != null)
        {
            _eventBehaviour.Handler.AddListener<CharacterDied>(OnCharacterDied);
        }
    }

    private void OnDisable()
    {
        if (_eventBehaviour != null)
        {
            _eventBehaviour.Handler.RemoveListener<CharacterDied>(OnCharacterDied);
        }
    }

    private void OnCharacterDied(CharacterDied died)
    {
        photonView.RPC("RPC_CharacterWon", PhotonTargets.All);
    }

    [PunRPC]
    private void RPC_CharacterWon()
    {
        UIManager.Instance.ShowOnly(WonMenu);
    }
}
