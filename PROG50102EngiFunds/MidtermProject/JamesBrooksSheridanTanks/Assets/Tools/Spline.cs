using System.Collections;
using System.Collections.Generic;
using UnityEngine;


[ExecuteInEditMode]
[RequireComponent(typeof(LineRenderer))]
public class Spline : MonoBehaviour {
    
    private float pingpongSign = 1.0f;    // Determines direction for pingpong mode
    private List<float> t;         // Variable t of catmulrom. List count should always = head list count

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

    [Range(1.0f, 60.0f)]
    public float dt = 1.0f;                      // Time between steps (1 - 60 seconds) or speed

    public List<GameObject> heads;

    public List<GameObject> contPoints = new List<GameObject>();
    

	// Use this for initialization
	void Start () {
		
        if (heads == null) {

            heads = new List<GameObject>();
        }
        if (t == null) {

            t = new List<float>();
        }

        // Create a t for each head
        foreach (GameObject head in heads) {

            t.Add(0.0f);
        }
    }

    public void AddHead(GameObject newHead) {

        heads.Add(newHead);
        t.Add(0.0f);
    }

    public void AddHeadAtPoint(GameObject newHead, GameObject point) {

        if (contPoints.Contains(point)) {

            heads.Add(newHead);
            t.Add(contPoints.IndexOf(point)-1);
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
        
        if (t.Count == heads.Count) {

            for (int i = 0; i < t.Count; i++) {

                float timeStep = 0.1f;
                float oldT = t[i];

                if (playType == PlayBackType.Constant_Time) {

                    timeStep = Time.deltaTime / (float)dt;  // dt used as seconds to complete interval
                }
                else {

                    timeStep = Time.deltaTime;  // Still move in relation to time passed
                }

                // Position modification
                if (gameMode == GameModes.None || gameMode == GameModes.Invalid) {

                    t[i] = 0.0f;
                }
                if (gameMode == GameModes.Forward) {

                    t[i] = t[i] + timeStep;

                    if (playType == PlayBackType.Constant_Speed) {

                        float distanceMag = Vector3.Magnitude(CatmullRomSpline(oldT) - CatmullRomSpline(t[i]));

                        t[i] = oldT + (timeStep / (distanceMag * 10.0f)) * (dt / 2.0f);    // Redo new t calculation (dt used as speed)
                    }

                    if (loop == true) {
                        if (t[i] > contPoints.Count) {

                            t[i] = 0.0f;
                        }
                    }
                    else if (t[i] > (contPoints.Count - 3)) {

                        t[i] = 0.0f;
                    }
                }
                else if (gameMode == GameModes.Backward) {

                    timeStep = -1.0f * timeStep;

                    t[i] = t[i] + timeStep;

                    if (playType == PlayBackType.Constant_Speed) {

                        float distanceMag = Vector3.Magnitude(CatmullRomSpline(oldT) - CatmullRomSpline(t[i]));

                        t[i] = oldT + (timeStep / (distanceMag * 10.0f)) * (dt / 2.0f);    // Redo new t calculation (dt used as speed)
                    }

                    if (loop == true && t[i] <= 0.0f) {

                        t[i] = contPoints.Count;
                    }
                    if (t[i] <= 0.0f) {

                        t[i] = contPoints.Count - 3.0f;
                    }
                }
                else if (gameMode == GameModes.PingPong) {

                    timeStep = pingpongSign * timeStep;

                    t[i] = t[i] + timeStep;

                    if (playType == PlayBackType.Constant_Speed) {

                        float distanceMag = Vector3.Magnitude(CatmullRomSpline(oldT) - CatmullRomSpline(t[i]));

                        t[i] = oldT + (timeStep / (distanceMag * 10.0f)) * (dt / 2.0f);    // Redo new t calculation (dt used as speed)
                    }

                    if (loop == true) {
                        // Go Backward
                        if (t[i] > contPoints.Count) {

                            t[i] = contPoints.Count;
                            pingpongSign = -1.0f;
                        }
                        // Go Forward
                        else if (t[i] <= 0.0f) {

                            t[i] = 0.0f;
                            pingpongSign = 1.0f;
                        }
                    }
                    else {
                        // Go Backward
                        if (t[i] >= (contPoints.Count - 3)) {

                            t[i] = contPoints.Count - 3.0f;
                            pingpongSign = -1.0f;
                        }
                        // Go Forward
                        else if (t[i] <= 0.0f) {

                            t[i] = 0.0f;
                            pingpongSign = 1.0f;
                        }
                    }
                }

                Vector3 newPos = CatmullRomSpline(t[i]);
                heads[i].transform.forward = newPos - heads[i].transform.position;


                if (heads[i] != null) {

                    heads[i].transform.SetPositionAndRotation(newPos, heads[i].transform.rotation);
                }
            }
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
