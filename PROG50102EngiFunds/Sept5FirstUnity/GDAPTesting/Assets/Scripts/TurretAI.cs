using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TurretAI : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
    private Vector3 FindTargetVector()
    {
        Component targetComp = GameObject.FindObjectOfType<TargetLogic>();
        GameObject target = null;
        Vector3 coords = new Vector3();


        if (targetComp != null)
        {
            target = targetComp.gameObject;

            coords = target.transform.position - this.transform.position;
        }

        return coords;
    }

    private void TurretMovementUpdate()
    {
        Vector3 targVec = FindTargetVector();
        Vector3 myVec = this.transform.right;
        Vector2 targVec2 = new Vector2(targVec.x, targVec.z);
        Vector2 myVec2 = new Vector2(myVec.x, myVec.z);

        float dotResult = Vector2.Dot(targVec2.normalized, myVec2.normalized);
        
        //this.transform.Rotate(Vector3.up, -1);
        
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
    
	// Update is called once per frame
	void Update () {

        TurretMovementUpdate();
	}
}
