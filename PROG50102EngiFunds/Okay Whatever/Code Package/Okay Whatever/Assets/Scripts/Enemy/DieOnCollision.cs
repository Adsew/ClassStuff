using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DieOnCollision : MonoBehaviour
{
    private void OnCollisionEnter(Collision collision)
    {
        GameObject go = collision.gameObject;
        if (go != null)
        {
            IsPlayer isPlayer = go.GetComponent<IsPlayer>();
            if (isPlayer != null)
            {
                removeGraphMove();
                isPlayer.Die();
            }
        }
    }

    private void removeGraphMove()
    {
        SplineMoveOnGraph moveScript = GetComponent<SplineMoveOnGraph>();
        if (moveScript != null)
        {
            Destroy(moveScript);
        }
    }

}
