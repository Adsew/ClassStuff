using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnTest : MonoBehaviour
{

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        //if (Input.GetKeyDown(KeyCode.Space))
        //{
        //    EnemyManager.Instance.spawnBarrel();
        //}
        if (Input.GetKeyDown(KeyCode.F))
        {
            EnemyManager.Instance.spawnFire();
        }
    }
}
