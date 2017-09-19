using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TurretAI : MonoBehaviour {

    public GameObject obj;
    public GameObject spawnLoc;

    private GameObject curTarget;
    private bool hasFired;

    private float timer;

    private const float TIME_PER_SHOT = 2;

    // Use this for initialization
    void Start () {

        hasFired = false;
        curTarget = null;
	}

    private void Fire()
    {
        if (obj != null && spawnLoc != null && hasFired == false && timer > TIME_PER_SHOT)
        {
            //this.gameObject.transform.position + new Vector3.forward
            Instantiate(obj, spawnLoc.transform.position, spawnLoc.transform.rotation);

            hasFired = true;
            curTarget = null;
            timer = 0;
        }
    }

    private GameObject FindTarget()
    {
        Component[] targetComp = (Component [])GameObject.FindObjectsOfType<TargetLogic>();
        GameObject target = null;

        if (curTarget == null)
        {
            if (targetComp.Length > 0)
            {
                double d = 0, tempD = 0;

                foreach (Component comp in targetComp)
                {
                    tempD = Vector3.Distance(this.transform.position, comp.gameObject.transform.position);

                    if (tempD > d)
                    {
                        target = comp.gameObject; // FIX THIS TO HIT SHORTEST TARGET
                        d = tempD;
                    }
                }
                
                hasFired = false;
            }
        }

        return target;
    }

    private void CrossTurretMovementUpdate()
    {
        GameObject target = null;
        Vector3 myVec = this.transform.forward;

        if (curTarget != null)
        {
            target = curTarget;
        }
        else
        {
            target = FindTarget();
        }

        // Error check for now
        if (target != null)
        {
            Vector3 targVec = target.transform.position - this.transform.position;
            Vector3 crossResult = Vector3.Cross(myVec, targVec);

            if (crossResult.y < 0.6 && crossResult.y > -0.6)
            {
                Fire();
            }

            // The problem is 0 could refer to the opposite direction,
            // need some kind of if to determine what way you are facing.
            if (crossResult.y > 0)
            {
                //turn left
                this.transform.Rotate(Vector3.up /*y*/, 1);
            }
            else if (crossResult.y < 0)
            {
                // turn right
                this.transform.Rotate(Vector3.up /*y*/, -1);
            }
        }
    }

    private void dotTurretMovementUpdate()
    {
        GameObject target = null;
        
        if (curTarget != null)
        {
            target = curTarget;
        }
        else
        {
            target = FindTarget();
        }
        
        if (target != null)
        {
            Vector3 targVec = target.transform.position - this.transform.position;

            Vector3 myVec = this.transform.right;
            Vector2 targVec2 = new Vector2(targVec.x, targVec.z);
            Vector2 myVec2 = new Vector2(myVec.x, myVec.z);

            float dotResult = Vector2.Dot(targVec2.normalized, myVec2.normalized);

            if (dotResult < 0.6 && dotResult > -0.6)
            {
                Fire();
            }

            // The problem is 0 could refer to the opposite direction,
            // need some kind of if to determine what way you are facing.
            if (dotResult > 0)
            {
                //turn left
                this.transform.Rotate(Vector3.up /*y*/, 1);
            }
            else if (dotResult < 0)
            {
                // turn right
                this.transform.Rotate(Vector3.up /*y*/, -1);
            }
        }
    }

    // Update is called once per frame
    void Update () {

        timer += Time.deltaTime;

        CrossTurretMovementUpdate();
	}
}
