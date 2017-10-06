using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovingPoint : MonoBehaviour {

    [Range(0,5)]
    public int maxXMove = 1;

    [Range(0, 5)]
    public int maxZMove = 1;

    // Position offset trackers
    private float xMove = 0;
    private float xDir = 1.0f;
    private float zMove = 0;
    private float zDir = 1.0f;

    Vector3 origPos;

	// Use this for initialization
	void Start () {

        Vector3 pos = this.gameObject.transform.position;
    }
	
    void MoveSideSide() {

        // Move game object uniformly along x and z axis within given bounds
        if (this.gameObject != null) {

            Vector3 pos = this.gameObject.transform.position;

            float xOffset = xDir * Time.deltaTime;
            float zOffset = zDir * Time.deltaTime;

            xMove = xMove + xOffset;
            zMove = zMove + zOffset;
            
            // Alternate direction at boundary
            if (Mathf.Abs(xMove) > maxXMove) {

                xDir = xDir * -1.0f;

                xMove = xMove - xOffset;    // Dont cross boundary

                xOffset = 0;    // Prevent offsetting that cross boundary
            }
            if (Mathf.Abs(zMove) > maxZMove) {

                zDir = zDir * -1.0f;

                zMove = zMove - zOffset;

                zOffset = 0;
            }

            pos.x = pos.x + xOffset;
            pos.z = pos.z + zOffset;

            this.gameObject.transform.position = pos;
        }
    }

	// Update is called once per frame
	void Update () {

        MoveSideSide();
	}
}
