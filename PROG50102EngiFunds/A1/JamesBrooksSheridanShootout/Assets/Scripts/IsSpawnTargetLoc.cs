using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsSpawnTargetLoc : IsSpawnLoc {

    public GameObject poleToSpawn;      // Pole target sits on

    [Range(1, 100)]
    public float spawnChance = 100.0f;

    // Use this for initialization
    void Start () {

        InitSpawnLoc();
	}

    new public void SpawnObject() {

        if (objToSpawn != null && poleToSpawn != null) {

            GameObject pole = Instantiate(poleToSpawn, myTransform.position, myTransform.rotation);

            if (pole != null) {

                // Generate offset to place target nicely on top of pole
                float y = myTransform.position.y
                    + (pole.transform.localScale.y / 2)
                    + (objToSpawn.transform.localScale.y / 2)
                    + 0.2f;

                Vector3 temp = new Vector3(myTransform.position.x, y, myTransform.position.z);

                GameObject target = Instantiate(objToSpawn, temp, objToSpawn.transform.rotation);

                // Now joint target to pole
                if (target != null) {

                    FixedJoint joint = pole.GetComponent<FixedJoint>();

                    if (joint != null) {

                        Rigidbody targRB = target.GetComponent<Rigidbody>();

                        if (targRB != null) {

                            joint.connectedBody = targRB;
                        }
                    }
                }
            }

        }
    }

    // Update is called once per frame
    void Update () {
		
	}
}
