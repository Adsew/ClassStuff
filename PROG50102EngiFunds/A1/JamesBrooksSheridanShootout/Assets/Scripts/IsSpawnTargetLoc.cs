using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsSpawnTargetLoc : IsSpawnLoc {

    public GameObject poleToSpawn;      // Pole target sits on

    // Use this for initialization
    void Start () {

        InitSpawnLoc();
	}

    new public void SpawnObject() {

        if (objToSpawn != null && poleToSpawn != null) {

            Instantiate(poleToSpawn, myTransform.position, myTransform.rotation);
            Instantiate(objToSpawn, myTransform.position, myTransform.rotation);
        }
    }

    // Update is called once per frame
    void Update () {
		
	}
}
