using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TargetSpawner : MonoBehaviour {

    /* Spawn Locations */

    private List<IsSpawnTargetLoc> spawnLocs;

    /* Timer Variables */

    private float timeTilSpawn;

    [Range(1,60)]
    public float timeBetweenSpawn = 1.0f; // Seconds (not gaurenteed every second)

    /* Randomizer */

    private System.Random rand = new System.Random();

    /* Functions */

	// Use this for initialization
	void Start () {

        // Dynamically get all spawn locations from the stage at runtime
        IsSpawnTargetLoc[] spawns = this.gameObject.GetComponentsInChildren<IsSpawnTargetLoc>();
        spawnLocs = new List<IsSpawnTargetLoc>();

        timeTilSpawn = 0;

        if (spawns.Length > 0) {

            foreach (IsSpawnTargetLoc sl in spawns) {

                if (sl.objToSpawn != null) {

                    spawnLocs.Add(sl);
                }
            }
        }
        else {

            Debug.Log("No spawn locations detected in " + this.gameObject.name);
        }
    }

    // Tell a random spawn location they can spawn.
    void SpawnRandTarget() {

        int i = rand.Next(0, spawnLocs.Count);
        int chance = rand.Next(1, 101);

        if (chance <= spawnLocs[i].spawnChance) {

            spawnLocs[i].SpawnObject();
        }
    }

    void SpawnTimer() {

        timeTilSpawn = timeTilSpawn + Time.deltaTime;

        if (timeTilSpawn > timeBetweenSpawn) {

            timeTilSpawn = 0;

            SpawnRandTarget();
        }
    }

	// Update is called once per frame
	void Update () {

        SpawnTimer();
	}
}
