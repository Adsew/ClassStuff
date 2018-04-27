using UnityEngine;

public class AttackInput : Photon.PunBehaviour
{
    public string attack;
    public string ability;
    private EventBehaviour _eventBehaviour;
    private AttackEvent _attackEvent = new AttackEvent();
    private AbilityEvent _abilityEvent = new AbilityEvent();

    private bool tvOSMode = false;
    private bool attackButtonHeld = false;
    private float attackButtonHeldTimer = 0.0f;

    public float holdTimeForSpecial = 0.5f;

    private void Start()
    {
        _eventBehaviour = GetComponent<EventBehaviour>();

        #if UNITY_TVOS
		    tvOSMode = true;
        #endif
    }

    // Update is called once per frame
    void Update()
    {
        // check that this object has local authority
        if (photonView.isMine)
        {
            CheckForInput();
        }
    }

    void CheckForInput()
    {
        // PC Controls
        if (!tvOSMode)
        {
            if (!string.IsNullOrEmpty(attack))
            {
                if (Input.GetButtonDown(attack))
                {
                    photonView.RPC("RPC_TriggerAttack", PhotonTargets.All);
                }
            }

            if (!string.IsNullOrEmpty(ability))
            {
                if (Input.GetButtonDown(ability))
                {
                    photonView.RPC("RPC_TriggerAbility", PhotonTargets.All);
                }
            }
        }
        // TvOS Controls
        else
        {
            if (Input.GetButton(attack))
            {
                attackButtonHeld = true;
                attackButtonHeldTimer += Time.deltaTime;
            }
            else
            {
                if (attackButtonHeld)
                {
                    if (attackButtonHeldTimer >= holdTimeForSpecial)
                    {
                        photonView.RPC("RPC_TriggerAbility", PhotonTargets.All);
                    }
                    else
                    {
                        photonView.RPC("RPC_TriggerAttack", PhotonTargets.All);
                    }

                    attackButtonHeld = false;
                    attackButtonHeldTimer = 0.0f;
                }
            }
        }
    }

    [PunRPC]
    private void RPC_TriggerAttack()
    {
        Debug.Log("Triggered Attack");
        if (_eventBehaviour != null)
        {
            Debug.Log("Firing Attack");
            _eventBehaviour.Handler.Invoke(_attackEvent);
        }
    }

    [PunRPC]
    private void RPC_TriggerAbility()
    {
        Debug.Log("Triggered Ability");
        if (_eventBehaviour != null)
        {
            Debug.Log("Firing Ability");
            _eventBehaviour.Handler.Invoke(_abilityEvent);
        }
    }
}
