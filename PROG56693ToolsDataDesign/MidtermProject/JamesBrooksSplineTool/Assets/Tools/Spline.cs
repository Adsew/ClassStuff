using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Spline : MonoBehaviour {
    
    private float pingpongSign = 1.0f;    // Determines direction for pingpong mode
    private float t = 0.0f;               // Variable t of catmulrom

    public List<GameObject> contPoints;
    
    public GameObject head;
    
    public enum GameModes {
        
        Forward,
        Backward,
        PingPong,
        Loop
    };
    public GameModes gameMode;

    public float speed;
    
	// Use this for initialization
	void Start () {
		
        // Backward starts at end
        if (gameMode == GameModes.Backward && contPoints.Count >= 4) {

            t = contPoints.Count - 2.0f;
        }
        else {

            t = 0.0f;
        }
    }

    void CatmullRomSpline() {
        
        // Ensure enough points for spline given position t
        if (contPoints.Count >= ((int)t + 4) || (gameMode == GameModes.Loop && contPoints.Count >= 4)) {

            // Calculate which points to be used (needed for loop mode)
            int i1 = (int)t;
            int i2 = i1 + 1;
            int i3 = i1 + 2;
            int i4 = i1 + 3;

            if (gameMode == GameModes.Loop) {
                
                // Wrap points around
                if (i2 > (contPoints.Count - 1)) {

                    i2 = i2 - contPoints.Count;
                }
                if (i3 > (contPoints.Count - 1)) {

                    i3 = i3 - contPoints.Count;
                }
                if (i4 > (contPoints.Count - 1)) {

                    i4 = i4 - contPoints.Count;
                }
            }

            if (contPoints[i1] != null
                && contPoints[i2] != null
                && contPoints[i3] != null
                && contPoints[i4] != null
                && head != null) {

                Vector3 newPosition;

                Vector3 p0 = contPoints[i1].transform.position;
                Vector3 p1 = contPoints[i2].transform.position;
                Vector3 p2 = contPoints[i3].transform.position;
                Vector3 p3 = contPoints[i4].transform.position;

                float catT = t - (int)t;    // Keep number between 0 and 1

                //Catmull rom equation converted
                newPosition = 0.5f * (
                    (p1 * 2.0f)
                    + (p2 - p0) * catT
                    + (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * catT * catT
                    + (3.0f * p1 - p0 - 3.0f * p2 + p3) * catT * catT * catT
                    );

                head.transform.SetPositionAndRotation(newPosition, head.transform.rotation);
            }
        }
    }

    void updatePositionUsingGameMode() {

        if (gameMode == GameModes.Forward) {

            t = t + Time.deltaTime;
            
            if (t > (contPoints.Count - 3)) {
                
                t = 0.0f;
            }
        }
        else if (gameMode == GameModes.Backward) {

            t = t - Time.deltaTime;
            
            if (t <= 0.0f) {

                t = contPoints.Count - 3.0f;
            }
        }
        else if (gameMode == GameModes.PingPong) {

            t = t + ( pingpongSign * Time.deltaTime );

            // Go backward
            if (t >= (contPoints.Count - 3)) {

                t = contPoints.Count - 3.0f;
                pingpongSign = -1.0f;
            }
            // Go forward
            else if (t <= 0.0f) {

                t = 0.0f;
                pingpongSign = 1.0f;
            }
        }
        else if (gameMode == GameModes.Loop) {

            t = t + Time.deltaTime;

            if (t > (contPoints.Count)) {

                t = 0.0f;
            }
        }
    }

    // Update is called once per frame
    void Update () {
        
        updatePositionUsingGameMode();
        CatmullRomSpline();
    }
}
