using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawner : MonoBehaviour {

    public GameObject obj;
    public KeyCode keyToCheck;

	// Use this for initialization
	void Start () {
		
	}
	
    private void SpawnerUpdate() {
        
        if (Input.GetKeyDown (keyToCheck) == true) {
            
            //make a copy
            if (obj != null) {

                Instantiate(obj);
            }
            //Debug.Log("SpawnerUpdate:: Object is null");
        }
    }

	// Update is called once per frame
	void Update () {
        SpawnerUpdate();
	}
}
