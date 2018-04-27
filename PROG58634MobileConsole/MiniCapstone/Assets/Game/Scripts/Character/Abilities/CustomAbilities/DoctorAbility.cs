using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DoctorAbility : BaseAbility
{
    GameCharacter gameCharacter;
    [Tooltip("Max amount of health that can be applied to character")]
    [Range(1, 100)]
    public int healMax = 5;
    [Tooltip("Max amount of damage that can be applied to character")]
    [Range(-100, -1)]
    public int damageMax = -1;

    private void Start()
    {
        gameCharacter = GetComponentInParent<GameCharacter>();
    }

    public override void Execute()
    {
        Debug.Log("Executing doctor ability");
        if (gameCharacter != null)
        {
            int amount = Random.Range(healMax, damageMax);

            if (amount < 0)
            {
                Debug.Log("taking damage");
                gameCharacter.TakeDamage(amount);
            }
            else if (amount > 0)
            {
                Debug.Log("healing: " + amount);
                gameCharacter.Heal(amount);
            }
            else
            {
                Debug.Log("Doctor ability was unlucky and produced no effect on character");
            }
        }
    }
}
