using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsSpawnCannonBallLoc : IsSpawnLoc {
    
    // Use this for initialization
    void Start() {

        InitSpawnLoc();
    }

    new public void SpawnObject() {

        if (objToSpawn != null) {

            Instantiate(objToSpawn,
                myTransform.position + Vector3.forward,
                myTransform.rotation);
        }
    }

    // Update is called once per frame
    void Update () {
		
	}
}
