using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DisableMovement : MonoBehaviour
{
    private FrostAbility ability;

    private void OnTriggerEnter(Collider other)
    {
        if (ability != null)
        {
            var movement = other.GetComponent<AIMovement>();
            if (movement != null)
            {
                ability.AddEffected(movement);
            }
        }
    }

    private void Start()
    {
        ability = GetComponentInParent<FrostAbility>();
    }
}
