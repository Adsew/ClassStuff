using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsSpawnLocMachinegun : IsSpawnLoc {

	// Use this for initialization
	void Start () {

        InitSpawnLoc();
	}

    public new IsProjectile SpawnObject() {

        if (objToSpawn != null) {
            
            GameObject temp = Instantiate(objToSpawn,
                myTransform.position + this.gameObject.transform.forward,
                myTransform.rotation);

            SoundMgr.This.PlayRandomFireSound();

            return temp.GetComponent<IsProjectile>();
        }

        return null;
    }

    // Update is called once per frame
    void Update () {
		
	}
}
