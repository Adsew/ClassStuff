using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AbilityDamage : MonoBehaviour
{
    BaseAbility ability;
    private void Awake()
    {
        ability = GetComponentInParent<BaseAbility>();
    }

    private void OnTriggerEnter(Collider other)
    {
        GameCharacter gameCharacter = other.GetComponent<GameCharacter>();
        if (gameCharacter != null)
        {
            if (ability != null)
            {
                ability.ApplyDamage(gameCharacter);
            }
        }
    }
}
