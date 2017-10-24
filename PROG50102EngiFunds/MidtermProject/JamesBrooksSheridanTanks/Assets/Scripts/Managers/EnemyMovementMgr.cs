using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyMovementMgr : MonoBehaviour {

    private List<Enemy> transferingEnemies;

    private Spline gTransferSpline = null;
    private Spline aTransferSpline = null;

    private GameObject gClosestSplineToPlayer = null;
    private GameObject aClosestSplineToPlayer = null;

    private float moveTankTime = 5.0f;

    public static EnemyMovementMgr This;

    public GameObject groundTransferSplineGO;
    public GameObject airTransferSplineGO;

    public float moveTimeInterval = 5.0f;
    
	// Use this for initialization
	void Start () {
		
        if (This == null) {

            This = this;
        }
        if (groundTransferSplineGO != null && airTransferSplineGO != null) {

            gTransferSpline = groundTransferSplineGO.GetComponent<Spline>();
            aTransferSpline = airTransferSplineGO.GetComponent<Spline>();
        }
        else {

            Debug.Log("EnemyMovementMgr: Missing a transfer spline.");
        }

        transferingEnemies = new List<Enemy>();
	}
	
    private void MoveEnemiesUpdate() {

        if (gTransferSpline != null && aTransferSpline != null) {

            // Tell a random tank to start rotating towards player every moveInterval seconds
            // Not gaurenteed to move a tank to add some randomness and avoid swarming player
            // all at once
            if (moveTankTime <= GameStateMgr.This.gameTime) {

                int i = Random.Range(0, EnemySpawnMgr.This.activeEnemies.Count);

                Enemy tank = EnemySpawnMgr.This.activeEnemies[i].GetComponent<Enemy>();

                moveTankTime = GameStateMgr.This.gameTime + moveTimeInterval;

                if (tank != null) {

                    // Check tank is not transfering already
                    // or not already on spline closest to player
                    if (!transferingEnemies.Contains(tank)
                        && (tank.myPath != gClosestSplineToPlayer.GetComponent<Spline>()
                            || tank.myPath != aClosestSplineToPlayer.GetComponent<Spline>())
                        && (tank.myPath != aTransferSpline
                            && tank.myPath != gTransferSpline)
                        ) {
                        
                        transferingEnemies.Add(tank);
                    }
                }
            }

            // Now handle already triggered tanks to exit to the transfer spline
            for (int i = 0; i < transferingEnemies.Count; i++) {

                Enemy tank = transferingEnemies[i];

                if (tank != null) {

                    GameObject point = tank.myPath.GetPrevPointForHead(tank.gameObject);

                    if (point != null) {

                        IsTransferPoint pInfo = point.GetComponent<IsTransferPoint>();

                        // This point links to transfer spline
                        if (pInfo != null) {
                            if (pInfo.connectedPoint != null) {

                                // Point is always child of spline
                                Spline splineToMoveTo = pInfo.connectedPoint.transform.parent.gameObject.GetComponent<Spline>();

                                if (splineToMoveTo != null) {

                                    tank.myPath.RemoveHead(tank.gameObject);
                                    tank.myPath = splineToMoveTo;
                                    splineToMoveTo.AddHeadAtPoint(tank.gameObject, pInfo.connectedPoint);

                                    transferingEnemies.Remove(tank);
                                    i--;
                                }
                            }
                        }
                    }
                }
                // Remove tank that died waiting to transfer
                else {

                    transferingEnemies.Remove(tank);
                    i--;
                }
            }
        }
    }

    private void TransferingEnemiesUpdate() {

        // Ground tanks on the transfer spline
        if (gTransferSpline != null) {

            for (int i = 0; i < gTransferSpline.heads.Count; i++) {

                Enemy tank = gTransferSpline.heads[i].GetComponent<Enemy>();
                GameObject point = tank.myPath.GetPrevPointForHead(tank.gameObject);

                if (point != null) {

                    IsTransferPoint pInfo = point.GetComponent<IsTransferPoint>();

                    // This point links to transfer pline, see if close
                    // enough to make seemless transition
                    if (pInfo != null) {
                        if (pInfo.connectedPoint != null) {

                            // Point must be child of spline
                            Spline splineToMoveTo = pInfo.connectedPoint.transform.parent.gameObject.GetComponent<Spline>();

                            if (splineToMoveTo != null) {

                                if (splineToMoveTo.gameObject == gClosestSplineToPlayer) {

                                    tank.myPath.RemoveHead(tank.gameObject);
                                    tank.myPath = splineToMoveTo;
                                    splineToMoveTo.AddHeadAtPoint(tank.gameObject, pInfo.connectedPoint);
                                    i--;
                                }
                            }
                        }
                    }
                }
            }
        }

        // Air tanks on the transfer spline
        if (aTransferSpline != null) {

            for (int i = 0; i < aTransferSpline.heads.Count; i++) {

                Enemy tank = aTransferSpline.heads[i].GetComponent<Enemy>();
                GameObject point = tank.myPath.GetPrevPointForHead(tank.gameObject);

                if (point != null) {

                    IsTransferPoint pInfo = point.GetComponent<IsTransferPoint>();

                    // This point links to transfer pline, see if close
                    // enough to make seemless transition
                    if (pInfo != null) {
                        if (pInfo.connectedPoint != null) {

                            // Point must be child of spline
                            Spline splineToMoveTo = pInfo.connectedPoint.transform.parent.gameObject.GetComponent<Spline>();

                            if (splineToMoveTo != null) {

                                if (splineToMoveTo.gameObject == aClosestSplineToPlayer) {

                                    tank.myPath.RemoveHead(tank.gameObject);
                                    tank.myPath = splineToMoveTo;
                                    splineToMoveTo.AddHeadAtPoint(tank.gameObject, pInfo.connectedPoint);
                                    i--;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    private void ClosestSplineUpdate() {

        // Find shortest ground path
        float shortest = -1.0f;

        foreach (GameObject s in EnemySpawnMgr.This.groundPaths) {

            float distance = Mathf.Abs(Vector3.Magnitude(
                s.transform.position - Player.This.pBodyGameObject.transform.position
                ));

            if (distance < shortest || shortest == -1.0f) {

                shortest = distance;
                gClosestSplineToPlayer = s;
            }
        }

        // Find shortest air path
        shortest = -1.0f;

        foreach (GameObject s in EnemySpawnMgr.This.airPaths) {

            float distance = Mathf.Abs(Vector3.Magnitude(
                s.transform.position - Player.This.pBodyGameObject.transform.position
                ));

            if (distance < shortest || shortest == -1.0f) {

                shortest = distance;
                aClosestSplineToPlayer = s;
            }
        }
    }

	// Update is called once per frame
	void Update () {

        ClosestSplineUpdate();
        MoveEnemiesUpdate();
        TransferingEnemiesUpdate();
	}
}
