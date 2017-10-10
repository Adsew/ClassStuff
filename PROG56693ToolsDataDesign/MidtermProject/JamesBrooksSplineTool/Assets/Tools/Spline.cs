﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;


[ExecuteInEditMode]
[RequireComponent(typeof(LineRenderer))]
public class Spline : MonoBehaviour {
    
    private float pingpongSign = 1.0f;    // Determines direction for pingpong mode
    private float t = 0.0f;               // Variable t of catmulrom

    private LineRenderer debugLine = null;

    public bool debug = true;
    public bool loop = false;

    public enum GameModes {

        Invalid,
        None,
        Forward,
        Backward,
        PingPong,
        Pause
    };
    public GameModes gameMode = GameModes.Forward;

    public enum PlayBackType {

        Constant_Time,
        Constant_Speed
    }
    public PlayBackType playType = PlayBackType.Constant_Time;

    [Range(1, 60)]
    public float dt;                      // Time between steps (1 - 60 seconds)

    public GameObject head = null;

    public List<GameObject> contPoints = new List<GameObject>();
    

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
        if (contPoints.Count >= 4) {

            // Calculate which points to be used (needed for loop mode)
            int i1 = (int)tVal;
            int i2 = i1 + 1;
            int i3 = i1 + 2;
            int i4 = i1 + 3;

            // Wrap points around
            if (i1 > (contPoints.Count - 1)) {

                i1 = i1 - contPoints.Count;
            }
            if (i2 > (contPoints.Count - 1)) {

                i2 = i2 - contPoints.Count;
            }
            if (i3 > (contPoints.Count - 1)) {

                i3 = i3 - contPoints.Count;
            }
            if (i4 > (contPoints.Count - 1)) {

                i4 = i4 - contPoints.Count;
            }
            
            if (contPoints[i1] != null
                && contPoints[i2] != null
                && contPoints[i3] != null
                && contPoints[i4] != null
                ) {

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
        
        float timeStep = 0.1f;
        float oldT = t;
        
        if (playType == PlayBackType.Constant_Time) {

            timeStep = Time.deltaTime / (float)dt;  // dt used as seconds to complete interval
        }
        
        // Position modification
        if (gameMode == GameModes.None || gameMode == GameModes.Invalid) {

            t = 0.0f;
        }
        if (gameMode == GameModes.Forward) {

            t = t + timeStep;

            if (playType == PlayBackType.Constant_Speed) {

                float distanceMag = Vector3.Magnitude(CatmullRomSpline(oldT) - CatmullRomSpline(t));

                t = oldT + ( timeStep / (distanceMag * 10.0f) ) * (dt / 2.0f);    // Redo new t calculation (dt used as speed)
            }

            if (loop == true) {
                if (t > contPoints.Count) {

                    t = 0.0f;
                }
            }
            else if (t > (contPoints.Count - 3)) {
                
                t = 0.0f;
            }
        }
        else if (gameMode == GameModes.Backward) {

            timeStep = -1.0f * timeStep;

            t = t + timeStep;

            if (playType == PlayBackType.Constant_Speed) {

                float distanceMag = Vector3.Magnitude(CatmullRomSpline(oldT) - CatmullRomSpline(t));

                t = oldT + (timeStep / (distanceMag * 10.0f)) * (dt / 2.0f);    // Redo new t calculation (dt used as speed)
            }

            if (loop == true && t <= 0.0f) {

                t = contPoints.Count;
            }
            if (t <= 0.0f) {

                t = contPoints.Count - 3.0f;
            }
        }
        else if (gameMode == GameModes.PingPong) {

            timeStep = pingpongSign * timeStep;

            t = t + timeStep;

            if (playType == PlayBackType.Constant_Speed) {

                float distanceMag = Vector3.Magnitude(CatmullRomSpline(oldT) - CatmullRomSpline(t));

                t = oldT + (timeStep / (distanceMag * 10.0f)) * (dt / 2.0f);    // Redo new t calculation (dt used as speed)
            }
            
            if (loop == true) {
                // Go Backward
                if (t > contPoints.Count) {

                    t = contPoints.Count;
                    pingpongSign = -1.0f;
                }
                // Go Forward
                else if (t <= 0.0f) {

                    t = 0.0f;
                    pingpongSign = 1.0f;
                }
            }
            else {
                // Go Backward
                if (t >= (contPoints.Count - 3)) {

                    t = contPoints.Count - 3.0f;
                    pingpongSign = -1.0f;
                }
                // Go Forward
                else if (t <= 0.0f) {

                    t = 0.0f;
                    pingpongSign = 1.0f;
                }
            }
        }

        Vector3 newPos = CatmullRomSpline(t);
        
        if (head != null) {

            head.transform.SetPositionAndRotation(newPos, head.transform.rotation);
        }
    }

    void UpdateDebugLine() {

        // Ensure we have required line component
        if (debugLine == null) {

            LineRenderer myLine = this.gameObject.GetComponent<LineRenderer>();

            if (myLine == null) {

                debugLine = this.gameObject.AddComponent<LineRenderer>();
            }
            else {

                debugLine = myLine;
            }

            debugLine.startWidth = 0.2f;
            debugLine.endWidth = 0.2f;
        }

        if (debug == true) {

            foreach (GameObject point in contPoints) {

                if (point != null) {

                    point.SetActive(true);
                }
            }

            if (contPoints.Count >= 4) { 

                int pointsToDraw;

                if (loop == true) {
                    
                    pointsToDraw = ((contPoints.Count) * 4) + 1;  // 4 points per segment + 1 for final point
                }
                else {

                    pointsToDraw = ((contPoints.Count - 3) * 4) + 1;  // 4 points per segment + 1 for final point
                }

                debugLine.positionCount = pointsToDraw;
                
                for (int i = 0; i < pointsToDraw - 1; i++) {

                    debugLine.SetPosition(i, CatmullRomSpline(i / 4.0f)); 
                }

                // Special case to draw perfectly to end point
                if (loop == true) {

                    debugLine.SetPosition(pointsToDraw - 1, contPoints[1].transform.position);
                }
                else {

                    debugLine.SetPosition(pointsToDraw - 1, contPoints[contPoints.Count-2].transform.position);
                }
            }
            // Not enough points to draw spline
            else {

                debugLine.positionCount = 0;
            }
        }
        else {

            debugLine.positionCount = 0;

            foreach (GameObject point in contPoints) {

                if (point != null) {

                    point.SetActive(false);
                }
            }
        }
    }

    // Ensure points list stays up to date to avoid errors
    private void RefreshPoints() {

        int i = 0;

        if (contPoints != null) {

            for (i = 0; i < contPoints.Count; i++) {

                if (contPoints[i] == null) {

                    contPoints.RemoveAt(i);
                    i--;
                }
            }
        }
    }

    // Update is called once per frame or when something moves in editor
    void Update () {

        RefreshPoints();
        UpdateDebugLine();

        if (Application.isPlaying) {

            UpdatePositionUsingGameMode();
        }
    }

    public void SetDebug(bool b) {

        debug = b;
    }

    public void SetMode(GameModes gm) {

        gameMode = gm;
    }
}
