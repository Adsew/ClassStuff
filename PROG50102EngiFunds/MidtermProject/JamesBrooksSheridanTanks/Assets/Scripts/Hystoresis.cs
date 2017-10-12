using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Hystoresis : MonoBehaviour {
    
    public GameObject trackObj;

    public float khMove = 0.05f;
    public float khFace = 0.2f;

    public enum FollowType { Behind, Facing };
    public FollowType followStyle = FollowType.Behind;

    public float followDistanceDiv = 2.0f;
    
    // IDEA USE SPLINE FOR CAMERA SETTINGS CAMERA TO FOLLOW ALONG PROJECTED PATH TO PLAYER, WHERE PLAYER IS GOING AND WHERE PLAYER WAS

	// Use this for initialization
	void Start () {
		
	}
	
    void SplineCameraFollow() {


    }

    void PlayerHysteresisUpdate() {

        Transform myTrans = this.transform;
        Transform trackTrans = trackObj.transform;
        
        if (trackObj != null) {
            
            Vector3 newPos;
            
            newPos = myTrans.position + khMove * (trackObj.transform.position - this.transform.position);

            // Stays distance behind target
            if (followDistanceDiv != 0 && followStyle == FollowType.Behind) {

                newPos -= trackTrans.forward / followDistanceDiv;
            }

            // Stays distance from target from last position
            else if (followDistanceDiv != 0 && followStyle == FollowType.Facing) {

                newPos -= myTrans.forward / followDistanceDiv;
            }

            // Slowly rotate to match target facing
            //Quaternion newRot = trackTrans.rotation;

            // Slowly rotate to look at target
            Quaternion newRot = Quaternion.LookRotation(trackTrans.position - myTrans.position);

            //float xRot, yRot, zRot;

            //xRot = myTrans.rotation.x + khFace * (newRot.x - myTrans.rotation.x);
            //yRot = myTrans.rotation.y + khFace * (newRot.y - myTrans.rotation.y);
            //zRot = myTrans.rotation.z + khFace * (newRot.z - myTrans.rotation.z);

            //newRot.x = xRot;
            //newRot.y = yRot;
            //newRot.z = zRot;
            
            myTrans.SetPositionAndRotation(newPos, newRot);
        }
    }

	// Update is called once per frame
	void Update () {

        PlayerHysteresisUpdate();
	}
}
