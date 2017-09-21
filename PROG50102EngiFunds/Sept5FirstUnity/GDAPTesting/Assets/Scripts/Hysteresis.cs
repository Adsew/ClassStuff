using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Hysteresis : MonoBehaviour {
    
    public float cameraFactor;

    [Range(1,2)]
    public float playerWeight = 1;
    
    public float kh;

    public List<GameObject> trackList;

	// Use this for initialization
	void Start () {
        
	}
	
    public void HysteresisUpdate() {
        
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
                if (gObj.GetComponent<IsPlayer>() != null) {

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

            newPos.x = xmax - (xmax - xmin)/2;
            newPos.z = zmax - (zmax - zmin)/2;
            
            newPos.y = (Mathf.Abs(xmax - xmin) + Mathf.Abs(zmax - zmin) + Mathf.Abs(ymax - ymin) )/cameraFactor + (ymax - (ymax - ymin)/2.0f);

            // Camera should only go so low
            if (newPos.y < 10) {

                newPos.y = 10.0f;
            }

            // P(t) += kh * (vDisp);
            this.transform.position += kh * (newPos - this.transform.position);
        }
    }

	// Update is called once per frame
	void Update () {

        HysteresisUpdate();
	}
}
