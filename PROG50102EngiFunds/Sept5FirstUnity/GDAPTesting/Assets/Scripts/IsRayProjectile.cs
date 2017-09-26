using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsRayProjectile : IsProjectile {

    public float dist = 100.0f;

	// Use this for initialization
	void Start () {
		
	}
	
    public void updateMovement() {

        Vector3 vStart = this.transform.position;
        Vector3 vDir = this.transform.forward;
        Vector3 vEnd = vStart + dist * vDir;
        
        RaycastHit hitInfo;

        bool hit = Physics.Raycast(vStart, vDir, out hitInfo, dist);

        if (hit) {

            Rigidbody rb = hitInfo.collider.gameObject.GetComponent<Rigidbody>();
            
            if (rb != null) {

                rb.isKinematic = true;

                this.transform.position = rb.transform.position;
            }
        }
    }

	// Update is called once per frame
	void Update () {

        updateMovement();
	}
}
