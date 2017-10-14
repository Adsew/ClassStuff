using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerCamera : MonoBehaviour {

    public GameObject playerTrackObj;
    public List<GameObject> trackList;
    
    [Range(1.0f, 2.0f)]
    public float playerWeight = 1;

    [Range(1.0f, 10.0f)]
    public float baseFollowDistance = 10.0f;
    public float baseFollowHeight = 2.0f;
    public float kh = 0.1f;

    // Use this for initialization
    void Start () {
		
        
	}

    // Camera Hysteresis to position behind player turret
    void CameraHysteresisUpdate() {
        
        if (playerTrackObj != null) {

            Transform myTrans = this.gameObject.transform;
            Transform trackTrans = playerTrackObj.transform;
            Vector3 newPos;

            float followHeight = baseFollowHeight;
            float followDistance = baseFollowDistance;

            newPos = myTrans.position + kh * (trackTrans.position - myTrans.position);
            
            newPos -= trackTrans.forward * followDistance;
            newPos.y += followHeight;

            myTrans.SetPositionAndRotation(newPos, trackTrans.rotation);
        }
    }

    public void CameraPositionTrackUpdate() {

        if (trackList.Count > 0) {

            Vector3 newPos;
            float xmin = 0, xmax = 0, ymin = 0, ymax = 0, zmin = 0, zmax = 0;

            // Gaurentee focus on singlular object or between n > 1 objects
            xmin = trackList[0].transform.position.x;
            xmax = trackList[0].transform.position.x;
            ymin = trackList[0].transform.position.y;
            ymax = trackList[0].transform.position.y;
            zmin = trackList[0].transform.position.z;
            zmax = trackList[0].transform.position.z;

            foreach (GameObject gObj in trackList) {

                Vector3 objPos = gObj.transform.position;

                // Add more weight to player.
                if (gObj.GetComponent<IsTurretHead>() != null) {

                    objPos.x = objPos.x * playerWeight;
                    objPos.y = objPos.y * playerWeight;
                    objPos.z = objPos.z * playerWeight;
                }

                if (objPos.x < xmin) {

                    xmin = objPos.x;
                }
                if (objPos.x > xmax) {

                    xmax = objPos.x;
                }
                if (objPos.y < ymin) {

                    ymin = objPos.y;
                }
                if (objPos.y > ymax) {

                    ymax = objPos.y;
                }
                if (objPos.z < zmin) {

                    zmin = objPos.z;
                }
                if (objPos.z > zmax) {

                    zmax = objPos.z;
                }
            }

            newPos.x = xmax - (xmax - xmin) / 2;
            newPos.y = ymax - (ymax - ymin) / 2;
            newPos.z = -(Mathf.Abs(xmax - xmin) + Mathf.Abs(ymax - ymin) + Mathf.Abs(zmax - zmin)) / baseFollowDistance + (zmax - (zmax - zmin) / 2.0f);

            // Camera should go so far back
            if (newPos.z < -10) {

                newPos.z = -10.0f;
            }
            
            // P(t) += kh * (vDisp);
            this.gameObject.transform.SetPositionAndRotation(
                this.gameObject.transform.position + kh * (newPos - this.gameObject.transform.position),
                this.gameObject.transform.rotation
                );
        }
    }

    // Update is called once per frame
    void Update () {

        //CameraHysteresisUpdate();
        CameraPositionTrackUpdate();
	}
}
