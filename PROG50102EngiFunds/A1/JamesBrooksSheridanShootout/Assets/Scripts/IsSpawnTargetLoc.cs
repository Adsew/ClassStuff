using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsSpawnTargetLoc : IsSpawnLoc {

    public GameObject poleToSpawn;      // Pole target sits on
    public GameObject despawnLoc;       // End point for the target

    [Range(1,30)]
    public int targTimeToCross = 2;     // Set targets time to cross the lane (seconds)

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

                Vector3 tempTrans = new Vector3(myTransform.position.x, y, myTransform.position.z);

                Quaternion spawnRot = this.gameObject.transform.rotation;
                spawnRot.x = spawnRot.x + objToSpawn.transform.rotation.x;
                spawnRot.y = spawnRot.y + objToSpawn.transform.rotation.y;
                spawnRot.z = spawnRot.z + objToSpawn.transform.rotation.z;

                GameObject target = Instantiate(objToSpawn, tempTrans, spawnRot);

                // Now joint target to pole
                if (target != null) {

                    FixedJoint joint = pole.GetComponent<FixedJoint>();

                    if (joint != null) {

                        Rigidbody targRB = target.GetComponent<Rigidbody>();

                        
                        if (targRB != null) {

                            joint.connectedBody = targRB;

                            // Everything set, so initialize target settings
                            TargetMovement poleSetter = pole.GetComponent<TargetMovement>();

                            if (poleSetter != null) {
                                
                                poleSetter.timeToCross = targTimeToCross;

                                // Each target has their own start and end points for spline
                                if (SplineMgr.This.splineLeft != null
                                    && SplineMgr.This.splineRight != null
                                    && this.despawnLoc != null) {
                                    
                                    poleSetter.contPoints.Add(SplineMgr.This.splineLeft);
                                    poleSetter.contPoints.Add(this.gameObject);
                                    poleSetter.contPoints.Add(this.despawnLoc);
                                    poleSetter.contPoints.Add(SplineMgr.This.splineRight);
                                }
                            }
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
