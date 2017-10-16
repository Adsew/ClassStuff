using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerCamera : MonoBehaviour {

    private GameObject cameraObj;
    
    public GameObject playerTrackObj;
    public List<GameObject> trackList;
    
    [Range(1.0f, 5.0f)]
    public float playerWeight = 1.0f;

    [Range(1.0f, 10.0f)]
    public float baseFollowDistance = 10.0f;
    [Range(-1.0f, 10.0f)]
    public float baseFollowHeight = 2.0f;

    public float kh = 0.1f;

    // Use this for initialization
    void Start () {
		
        if (trackList == null) {

            trackList = new List<GameObject>();
        }

        if (cameraObj == null) {

            Camera temp = GetComponentInChildren<Camera>();

            if (temp != null) {

                cameraObj = temp.gameObject;
            }
        }
	}

    // Camera Hysteresis to position behind player turret
    void CameraPositionUpdate() {
        
        if (playerTrackObj != null && cameraObj != null) {

            Transform myTrans = this.gameObject.transform;
            Transform playerTrans = playerTrackObj.transform;
            Transform camTrans = cameraObj.transform;
            Vector3 newPos;
            Quaternion newRot;
            
            // Set base position
            newPos = playerTrans.position - playerTrans.forward * baseFollowDistance;
            newPos.y += baseFollowHeight;

            newPos = myTrans.position + kh * (newPos - myTrans.position);

            // Rotate to match player turret, maintain ground evenness
            newRot = playerTrans.localRotation;
            newRot.x = 0.0f;
            newRot.z = 0.0f;

            myTrans.SetPositionAndRotation(newPos, newRot);

            // Offset the camera based on enemies close in the view
            // Having camera inside empty object allows local position
            // offseting for more dynamic camera with enemies
            Vector3 offset = EnemyViewVectorOffset();
            Vector3 cross = Vector3.Cross(offset, myTrans.forward);
            
            offset.y = offset.y / 2.0f;
            offset.z = 0.0f;
            offset.x = 0.0f;

            offset += -(cross.y / 2.0f) * Vector3.right;

            camTrans.localPosition += kh * (offset - camTrans.localPosition);
            camTrans.rotation = newRot;
        }
    }

    private Vector3 EnemyViewVectorOffset() {

        float xmin = 0, xmax = 0, ymin = 0, ymax = 0, zmin = 0, zmax = 0;
        Vector3 offset;
        
        if (playerTrackObj != null) {

            // Gaurentee focus on singlular object or between n > 1 objects
            Vector3 playPos = playerTrackObj.transform.position - this.gameObject.transform.position;

            xmin = playPos.x - playerWeight;
            xmax = playPos.x + playerWeight;
            ymin = playPos.y - playerWeight;
            ymax = playPos.y + playerWeight;
            zmin = playPos.z - playerWeight;
            zmax = playPos.z + playerWeight;
        }
        
        if (trackList.Count > 0) {
            
            foreach (GameObject gObj in trackList) {

                if (gObj != null) {

                    Vector3 objPos = gObj.transform.position - this.gameObject.transform.position;

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
            }
        }

        offset.x = xmax - (xmax - xmin) / 2.0f;
        offset.y = ymax - (ymax - ymin) / 2.0f;
        offset.z = zmax - (zmax - zmin) / 2.0f;
        
        return offset;
    }

    // Update is called once per frame
    void Update () {

        CameraPositionUpdate();
	}
}
