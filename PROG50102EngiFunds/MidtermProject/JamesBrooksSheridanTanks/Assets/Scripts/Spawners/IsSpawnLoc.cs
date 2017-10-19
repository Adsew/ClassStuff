using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class IsSpawnLoc : MonoBehaviour {

    public GameObject objToSpawn;
    
    protected Transform myTransform;

	// Use this for initialization
	void Start () {

        
	}

    // Must always be called in child Start function
    protected void InitSpawnLoc() {

        if (this.gameObject != null) {

            myTransform = this.gameObject.transform;
        }
    }

    public virtual void SpawnObject() {

        if (objToSpawn != null) {
            
            Instantiate(objToSpawn, myTransform.position, myTransform.rotation);
        }
    }

	// Update is called once per frame
	void Update () {
		
	}
}
