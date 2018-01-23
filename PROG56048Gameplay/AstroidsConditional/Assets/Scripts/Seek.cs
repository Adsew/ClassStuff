using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Seek : MonoBehaviour {

    private Vector3 velocity = new Vector3(0, 0, 0);

    public GameObject trackObj = null;

    public bool fleeing = false;

    public float maxFleeDistance = 10.0f;

    public float maxSpeed = 1.0f;
    public float acceleration = 0.01f;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
        movementUpdate();
	}

    void movementUpdate() {

        if (trackObj != null) {

            Vector3 desiredDir = Vector3.Normalize(trackObj.transform.position - transform.position);

            if (fleeing) {

                desiredDir *= -1.0f;
            }

            velocity += desiredDir * acceleration;

            // Cap speed at max
            if (Vector3.Magnitude(velocity) > maxSpeed) {

                velocity = velocity * (maxSpeed / Vector3.Magnitude(velocity));
            }

            // Limit distance if fleeing / slowdown
            if (fleeing && Mathf.Abs(Vector3.Magnitude(trackObj.transform.position - transform.position)) > maxFleeDistance) {

                velocity = new Vector3(0, 0, 0);
            }
            // Else move normaly at velocity
            else {

                transform.position += velocity;
            }
        }
    }
}
