using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsSpawnLocMachinegun : IsSpawnLoc {

	// Use this for initialization
	void Start () {

        InitSpawnLoc();
	}

    public new void SpawnObject() {

        if (objToSpawn != null) {
            
            Instantiate(objToSpawn,
                myTransform.position + this.gameObject.transform.forward,
                myTransform.rotation);

            SoundMgr.This.PlayRandomFireSound();
        }
    }

    // Update is called once per frame
    void Update () {
		
	}
}
