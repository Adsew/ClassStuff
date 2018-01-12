using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScoreOnTouch : MonoBehaviour
{
    void OnTriggerEnter(Collider other)
    {
        GameObject go = other.gameObject;
        if (go.GetComponent<IsPlayer>())
        {
            ScoreManager.Instance.scorePickupable();
            Destroy(this.gameObject);
            AudioController a = GetComponent<AudioController>();
            if (a != null)
            {
                a.PlayClip();
            }
        }
    }
}
