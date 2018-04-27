using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BigBerthaAbility : BaseAbility
{
    [Range(-100, -1)]
    public int Damage;
    private BoxCollider abilityCollider;
    public GameObject groundEffect;

    public override void Execute()
    {
        photonView.RPC("RPC_TriggerSpecialEffect", PhotonTargets.All);

        ToggleColliders(true);
    }

    public override void Finish()
    {
        ToggleColliders(false);
    }

    private void ToggleColliders(bool value)
    {
        if (abilityCollider != null)
        {
            abilityCollider.gameObject.SetActive(value);
        }
    }

    public override void ApplyDamage(GameCharacter gameCharacter)
    {
        if (gameCharacter != null)
        {
            gameCharacter.TakeDamage(Damage);
        }
    }

    // Use this for initialization
    void Start()
    {
        abilityCollider = GetComponentInChildren<BoxCollider>();
        ToggleColliders(false);
    }

    [PunRPC]
    protected void RPC_TriggerSpecialEffect()
    {
        if (groundEffect != null)
        {
            Instantiate(groundEffect, transform.position, transform.rotation);
        }
    }
}
