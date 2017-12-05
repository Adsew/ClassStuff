using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsPickupable : MonoBehaviour {

    public GameObject pickupTrigger;
    public IsPickupTrigger trigger;

    public AnimatorOverrideController animOverride;

    public List<GameObject> rightHandPoints;
    public List<GameObject> leftHandPoints;

	// Use this for initialization
	void Start () {
		
        if (trigger == null && pickupTrigger != null) {

            trigger = pickupTrigger.GetComponent<IsPickupTrigger>();
        }

        if (rightHandPoints.Count == 0) {

            IsRHPoint[] rhs = this.gameObject.GetComponentsInChildren<IsRHPoint>();

            foreach (IsRHPoint rh in rhs) {

                rightHandPoints.Add(rh.gameObject);
            }
        }

        if (leftHandPoints.Count == 0) {

            IsLHPoint[] lhs = this.gameObject.GetComponentsInChildren<IsLHPoint>();

            foreach (IsLHPoint lh in lhs) {

                leftHandPoints.Add(lh.gameObject);
            }
        }
    }
	
	// Update is called once per frame
	void Update () {
		
	}

    public GameObject getClosestHandle(Vector3 pos) {

        GameObject closestGO = null;
        float shortestDist = 0;
        float distance = 0;

        foreach (GameObject handle in rightHandPoints) {

            if (closestGO == null) {

                closestGO = handle;

                shortestDist = Mathf.Abs(Vector3.Magnitude(handle.transform.position - pos));
            }
            else {

                distance = Mathf.Abs(Vector3.Magnitude(handle.transform.position - pos));

                if (distance < shortestDist) {

                    shortestDist = distance;
                    closestGO = handle;
                }
            }
        }

        return closestGO;
    }
}
