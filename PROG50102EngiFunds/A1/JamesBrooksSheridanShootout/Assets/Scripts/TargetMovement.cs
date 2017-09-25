using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TargetMovement : MonoBehaviour {

    [Range(1, 30)]
    public int timeToCross;

    private float t;

    public List<GameObject> contPoints;
    
    
	// Use this for initialization
	void Start () {

        t = 0;
	}

    void UpdateTimer() {

        t = t + (Time.deltaTime / (float)timeToCross);
    }

    void CatmullRomSpline() {
        
        // MUST have 4 points.
        if (contPoints.Count == 4
            && contPoints[0] != null
            && contPoints[1] != null
            && contPoints[2] != null
            && contPoints[3] != null) {
            
            Vector3 newPosition;

            Vector3 p0 = contPoints[0].transform.position;
            Vector3 p1 = contPoints[1].transform.position;
            Vector3 p2 = contPoints[2].transform.position;
            Vector3 p3 = contPoints[3].transform.position;

            //Catmull rom equation converted
            newPosition = 0.5f * (
                (p1 * 2.0f)
                + (p2 - p0) * t
                + (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t * t
                + (3.0f * p1 - p0 - 3.0f * p2 + p3) * t * t * t
                );

            this.gameObject.transform.SetPositionAndRotation(newPosition, this.gameObject.transform.rotation);
        }
    }

    void determineDeath() {

        // Reached end of spline, target will drop to floor for fun
        if (t >= 1.0f) {

            Destroy(this.gameObject);
        }
    }

    // Update is called once per frame
    void Update () {

        UpdateTimer();
        CatmullRomSpline();
        determineDeath();
	}
}
