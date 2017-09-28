using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour {

    public float h, v;
    public float speed = 1.0f;


    public GameObject playerTrackObj;

    public float followDistanceDiv = 2.0f;
    public float kh = 1.0f;

    private Vector3 vDisp;

    // Use this for initialization
    void Start () {
		
	}

    void CameraHysteresisUpdate() {

        Transform myTrans = this.transform;
        Transform trackTrans = playerTrackObj.transform;

        if (playerTrackObj != null) {
            
            Vector3 newPos;

            newPos = myTrans.position + ( kh * (trackTrans.position - myTrans.position) );

            if (followDistanceDiv != 0) {

                newPos -= trackTrans.forward / followDistanceDiv;
            }

            myTrans.SetPositionAndRotation(newPos, myTrans.rotation);
        }
    }

    void PlayerCtrlUpdate() {

        Vector3 newTrackPos;

        h = Input.GetAxis("Horizontal");
        v = Input.GetAxis("Vertical");

        vDisp = new Vector3(0.0f, 0.0f, v);
        vDisp *= speed;

        h *= speed * 2;

        if (playerTrackObj != null) {

            playerTrackObj.transform.Translate(vDisp);

            this.transform.Rotate(0.0f, h, 0.0f);

            // Now update positoin of track relative to new cam rotation
            float dist = Vector3.Magnitude(playerTrackObj.transform.position - this.transform.position); // Get distance
            newTrackPos = this.transform.position + dist * this.transform.forward;

            playerTrackObj.transform.SetPositionAndRotation(newTrackPos, this.transform.rotation);
        }
    }

	// Update is called once per frame
	void Update () {

        PlayerCtrlUpdate();
        CameraHysteresisUpdate();
	}
}
