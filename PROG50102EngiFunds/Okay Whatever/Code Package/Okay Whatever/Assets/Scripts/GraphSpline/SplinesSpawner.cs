using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SplinesSpawner : MonoBehaviour
{
    public bool constantSpeed;
    public bool folowPlayer = false;
    public GameObject p1;
    public GameObject p2;
    public GameObject p3;
    public GameObject p4;

    [Range(0.0f, 0.3f)]
    public float dt;

    public void spawnObject(GameObject obj)
    {
        SplineMoveOnGraph sp = obj.GetComponent<SplineMoveOnGraph>();
        if (sp == null)
        {
            sp = obj.AddComponent<SplineMoveOnGraph>();
        }
        if (sp != null)
        {
            sp.folowPlayer = folowPlayer;
            sp.p1 = p1;
            sp.p2 = p2;
            sp.p3 = p3;
            sp.p4 = p4;
            sp.dt = dt;
            sp.constantSpeed = constantSpeed;
            sp.t = 0;
        }
    }
}
