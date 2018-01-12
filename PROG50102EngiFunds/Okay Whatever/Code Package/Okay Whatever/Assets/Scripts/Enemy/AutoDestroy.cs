using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AutoDestroy : MonoBehaviour
{

    public float secondsToDestroy = 5.0f;

    // Update is called once per frame
    void Update()
    {
        secondsToDestroy -= Time.deltaTime;
        if (secondsToDestroy < 0)
        {
            EnemyManager.Instance.removeEnemy(this.gameObject);
            Destroy(this.gameObject);
        }
    }
}
