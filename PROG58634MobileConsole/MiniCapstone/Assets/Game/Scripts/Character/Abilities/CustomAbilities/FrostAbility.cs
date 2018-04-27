using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FrostAbility : BaseAbility
{
    public ParticleSystem snowflakes;
    [SerializeField]
    private List<AIMovement> effected = new List<AIMovement>();
    private BoxCollider abilityCollider;

    public override void Execute()
    {
        Debug.Log("Execute Frost ability");
        effected.Clear();
        ToggleColliders(true);
        photonView.RPC("RPC_TriggerSpecialEffect", PhotonTargets.All);
    }

    public override void Finish()
    {
        Debug.Log("Finish Frost ability");
        ToggleColliders(false);
        foreach (var movement in effected)
        {
            movement.CanMove = true;
        }
        effected.Clear();
    }

    public void AddEffected(AIMovement movement)
    {
        if (movement != null)
        {
            movement.CanMove = false;
            effected.Add(movement);
        }
    }

    private void ToggleColliders(bool value)
    {
        if (abilityCollider != null)
        {
            abilityCollider.gameObject.SetActive(value);
        }
    }

    private void Start()
    {
        abilityCollider = GetComponentInChildren<BoxCollider>();
        ToggleColliders(false);
    }

    [PunRPC]
    protected void RPC_TriggerSpecialEffect()
    {
        if (snowflakes != null)
        {
            Instantiate(snowflakes, transform.position, transform.rotation);
        }
    }
}
