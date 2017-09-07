using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Spawner : MonoBehaviour {

    public GameObject obj;
    public KeyCode keyToCheck;
    private GameObject spawnLoc;

	// Use this for initialization
	void Start () {

        //spawnLoc = GameObject.FindGameObjectWithTag("SpawnLoc");
        IsSpawnLoc s1 = this.gameObject.GetComponentInChildren<IsSpawnLoc>();

        if (s1 != null) {

            spawnLoc = s1.gameObject;
        }
        
        Debug.Log("Start is finished.");
	}
	
    private void SpawnerUpdate() {
        
        if (Input.GetKeyDown (keyToCheck) == true) {
            
            //make a copy
            if (obj != null && spawnLoc != null) {
                //this.gameObject.transform.position + new Vector3.forward
                Instantiate(obj, spawnLoc.transform.position, spawnLoc.transform.rotation);
            }
            //Debug.Log("SpawnerUpdate:: Object is null");
        }
    }

	// Update is called once per frame
	void Update () {
        SpawnerUpdate();
	}
}
