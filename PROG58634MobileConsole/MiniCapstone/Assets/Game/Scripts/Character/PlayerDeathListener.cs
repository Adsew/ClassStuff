using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerDeathListener : Photon.PunBehaviour {

    private EventBehaviour _eventBehaviour;

    public string DeathScreen = "PlayerDied";

	// Use this for initialization
	void Start ()
    {
        _eventBehaviour = GetComponent<EventBehaviour>();
	}

    public void OnEnable()
    {
        if (_eventBehaviour == null)
        {
            _eventBehaviour = GetComponent<EventBehaviour>();
        }

        if (_eventBehaviour != null)
        {
            _eventBehaviour.Handler.AddListener<CharacterDied>(OnCharacterDeath);
        }
    }

    public void OnDisable()
    {
        if (_eventBehaviour != null)
        {
            _eventBehaviour.Handler.RemoveListener<CharacterDied>(OnCharacterDeath);
        }
    }

    private void OnCharacterDeath(CharacterDied died)
    {
        photonView.RPC("RPC_OnPlayerHasDied", PhotonTargets.All);
    }

    [PunRPC]
    public void RPC_OnPlayerHasDied()
    {
        UIManager.Instance.ShowOnly(DeathScreen);

        if (photonView.isMine)
        {
            PhotonNetwork.Destroy(gameObject);
        }
    }
}
