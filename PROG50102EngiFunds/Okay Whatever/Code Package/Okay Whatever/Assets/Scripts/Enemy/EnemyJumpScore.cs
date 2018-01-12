using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyJumpScore : MonoBehaviour
{
    public int pointsOnTrigger = 10;

    void OnTriggerEnter(Collider other)
    {
        GameObject tgt = other.gameObject;
        IsPlayer isPlayer = tgt.GetComponent<IsPlayer>();
        if (isPlayer != null)
        {
            ScoreManager.Instance.scoreJumpOver();
            Destroy(this);
        }
    }
}
