using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RaycastObj : MonoBehaviour {

    // visualize state of our ray
    public bool debug;
    public Color drawCol;
    public Color hitCol;
    public Color missCol;

    public float dist;
    public Vector3 vDir;
    public bool hit;

	// Use this for initialization
	void Start () {
		
	}
	
    public void RaycastObjUpdate() {

        Vector3 vStart = this.transform.position;
        Vector3 vEnd = vStart + dist * vDir;

        // Check reycast hit something, if does stop obj

        RaycastHit hitInfo; // Will pass us info similar to oncollisionenter

        hit = Physics.Raycast(vStart, vDir, out hitInfo, dist);

        drawCol = missCol;

        if (hit) {

            // sto the obj
            drawCol = hitCol;

            Rigidbody rb = this.GetComponent<Rigidbody>();

            if (rb != null) {

                rb.isKinematic = true;
            }
        }

        if (debug == true) {

            Debug.DrawLine(vStart, vEnd, drawCol);
        }
    }

	// Update is called once per frame
	void Update () {

        RaycastObjUpdate();
	}
}
