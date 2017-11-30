using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsPickupable : MonoBehaviour {

    public GameObject rightHandPoint;
    public GameObject leftHandPoint;

	// Use this for initialization
	void Start () {
		
        if (rightHandPoint == null) {

            IsRHPoint rh = this.gameObject.GetComponentInChildren<IsRHPoint>();

            if (rh != null) {

                rightHandPoint = rh.gameObject;
            }
        }

        if (leftHandPoint == null) {

            IsLHPoint lh = this.gameObject.GetComponentInChildren<IsLHPoint>();

            if (lh != null) {

                leftHandPoint = lh.gameObject;
            }
        }
    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
