﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Spline : MonoBehaviour {
    
    private float pingpongSign = 1.0f;    // Determines direction for pingpong mode
    private float t = 0.0f;               // Variable t of catmulrom

    public bool debug;

    [Range(1,60)]
    public float dt;                      // Time between steps (1 - 60 seconds)

    public enum GameModes {

        Invalid,
        None,
        Forward,
        Backward,
        PingPong,
        Loop,
        Pause
    };
    public GameModes gameMode;

    public enum PlayBackType {

        Constant_Time,
        Constant_Speed
    }
    public PlayBackType playType;

    public GameObject head;

    public List<GameObject> contPoints;
    

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

    Vector3 CatmullRomSpline(float tVal) {
        
        // Ensure enough points for spline given position t
        if (contPoints.Count >= ((int)tVal + 4) || (gameMode == GameModes.Loop && contPoints.Count >= 4)) {

            // Calculate which points to be used (needed for loop mode)
            int i1 = (int)tVal;
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

                float catmulT = tVal - (int)tVal;    // Keep number between 0 and 1

                //Catmull rom equation converted
                newPosition = 0.5f * (
                    (p1 * 2.0f)
                    + (p2 - p0) * catmulT
                    + (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * catmulT * catmulT
                    + (3.0f * p1 - p0 - 3.0f * p2 + p3) * catmulT * catmulT * catmulT
                    );
                
                return newPosition;
            }
        }

        return new Vector3(0.0f, 0.0f, 0.0f);
    }

    void UpdatePositionUsingGameMode() {

        float timeStep = Time.deltaTime / (float)dt;

        if (gameMode == GameModes.Forward) {

            t = t + timeStep;
            
            if (t > (contPoints.Count - 3)) {
                
                t = 0.0f;
            }
        }
        else if (gameMode == GameModes.Backward) {

            t = t - timeStep;
            
            if (t <= 0.0f) {

                t = contPoints.Count - 3.0f;
            }
        }
        else if (gameMode == GameModes.PingPong) {

            t = t + ( pingpongSign * timeStep);

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

            t = t + timeStep;

            if (t > (contPoints.Count)) {

                t = 0.0f;
            }
        }
        Vector3 newPos = CatmullRomSpline(t);

        head.transform.SetPositionAndRotation(newPos, head.transform.rotation);
    }

    // Update is called once per frame
    void Update () {
        
        UpdatePositionUsingGameMode();
    }
}
