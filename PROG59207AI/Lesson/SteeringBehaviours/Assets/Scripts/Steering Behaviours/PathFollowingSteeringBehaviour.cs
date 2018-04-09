using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PathFollowingSteeringBehaviour : ArriveSteeringBehaviour {

    public float waypointSeekDistance = 0.5f;
    public bool loop = false;

    public int currentIndex = 0;
    public List<Transform> waypoints = new List<Transform>();

	// Use this for initialization
	void Start () {
		
        if (waypoints != null && waypoints.Count > 0)
        {
            Target = waypoints[0].position;
        }
	}

    public override Vector3 calculateForce()
    {
        if (waypoints == null || waypoints.Count == 0)
        {
            return Vector3.zero;
        }

        // Arrive at end of path
        if (currentIndex >= waypoints.Count - 1 && loop == false)
        {
            return base.calculateForce();
        }
        else
        {
            if ((waypoints[currentIndex].position - gameObject.transform.position).magnitude < waypointSeekDistance)
            {
                currentIndex++;
                if (currentIndex >= waypoints.Count)
                {
                    currentIndex = 0;
                }
            }

            Target = waypoints[currentIndex].position;

            return base.calculateForce();
        }
    }
}
