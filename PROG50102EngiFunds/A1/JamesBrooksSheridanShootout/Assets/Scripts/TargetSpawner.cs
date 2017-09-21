using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TargetSpawner : MonoBehaviour {

    private List<GameObject> spawnLocs;

	// Use this for initialization
	void Start () {
        
        // Dynamically get all spawn locations from the stage at runtime
        Component[] spawns = this.gameObject.GetComponentsInChildren<IsSpawnLoc>();
        spawnLocs = new List<GameObject>();

        if (spawns.Length > 0) {

            foreach (Component comp in spawns) {

                if (comp.gameObject != null) {

                    spawnLocs.Add(comp.gameObject);
                }
            }
        }
        else {

            Debug.Log("No spawn locations detected in " + this.gameObject.name);
        }
    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
