using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DieWhenFall : MonoBehaviour
{

    void OnTriggerEnter(Collider other)
    {
        GameObject go = other.gameObject;
        IsPlayer isPlayer = go.GetComponent<IsPlayer>();
        if (isPlayer != null)
        {
            isPlayer.Die();
        }
    }
}
