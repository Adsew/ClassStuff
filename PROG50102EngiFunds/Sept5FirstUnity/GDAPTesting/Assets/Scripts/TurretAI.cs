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

            coords = target.transform.position + this.transform.position;
        }

        return coords;
    }

    private void TurretMovementUpdate()
    {
        Vector3 targVec = FindTargetVector();
        Vector3 myVec = this.transform.forward;
        Vector2 targVec2 = new Vector2(targVec.x, targVec.z);
        Vector2 myVec2 = new Vector2(myVec.x, myVec.y);

        float dotResult = Vector2.Dot(targVec2, myVec2);
        float angleResult = Vector2.Angle(targVec2, myVec2);

        if (angleResult < 180 && angleResult > 0)
        {
            //turn left
            this.transform.Rotate(Vector3.up /*y*/, -1);
        }
        else if (angleResult >= 180)
        {
            //turn right
            this.transform.Rotate(Vector3.up /*y*/, 1);
        }
        else if (angleResult == 0)
        {
            this.transform.Rotate(Vector3.up /*y*/, (float)0.0);
        }
    }
    
	// Update is called once per frame
	void Update () {

        TurretMovementUpdate();
	}
}
