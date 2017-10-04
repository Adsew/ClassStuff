using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

[InitializeOnLoad]
public class SplineTool {

    /*
     * THINGS TO IMPLEMENTS
     * 
     * Adding spline \
     * adding spline node to created spline  \
     * setting start of spline
     * loading splines back into tool on startup
     * saveing loading splines to xml
     * Draw line with debug mode
    */
    
    private static List<GameObject> splines;   // All splines in the scenes

    private static GameObject workingSpline;
    

    // Called on unity launch
    // Done to get already made splines on opening a project
    static SplineTool() {

        GetAllSplinesInScene();
    }

    // Gets all splines in the scene for further use
    // Used only as a safety fallback after initial use on startup
    [MenuItem("JB Tools/Spline/Refresh Active Splines")]
    private static void GetAllSplinesInScene() {

        Component[] inSceneSplines = GameObject.FindObjectsOfType<Spline>();

        splines = new List<GameObject>();   // Gaurentee no doubling splines in list by reseting it

        foreach (Component s in inSceneSplines) {

            splines.Add(s.gameObject);
        }

        // Change working object to something usable if any exist
        if (workingSpline == null && splines.Count > 0) {

            workingSpline = splines[0];
        }
    }

    // Creates a new spline
    [MenuItem("JB Tools/Spline/New Spline")]
    public static void CreateNewSpline() {
        
        if (splines == null) {

            GetAllSplinesInScene();
        }

        GameObject emptySpline = new GameObject("New Spline " + splines.Count);

        if (emptySpline != null) {

            emptySpline.AddComponent<Spline>();

            splines.Add(emptySpline);

            workingSpline = emptySpline;
        }
    }
    
    // Add point to current working spline
    [MenuItem("JB Tools/Spline/Add Point")]
    public static void AddSplinePoint() {

        if (workingSpline != null) {

            GameObject newPoint = GameObject.CreatePrimitive(PrimitiveType.Sphere);

            // Add the new point as child of spline and add to spline's list
            if (newPoint != null) {

                Spline sp = workingSpline.GetComponent<Spline>();

                if (sp != null) {

                    newPoint.name = "Spline Point";
                    newPoint.transform.localScale = new Vector3(0.2f, 0.2f, 0.2f);
                    newPoint.transform.parent = workingSpline.transform;

                    if (sp.contPoints == null) {

                        sp.contPoints = new List<GameObject>();
                    }

                    sp.contPoints.Add(newPoint);
                }
                else {

                    Debug.Log("Can't add point to spline. No spline selected.");

                    GameObject.Destroy(newPoint);
                }
            }
        }
        else {

            Debug.Log("No spline selected. Select spline before adding a point.");
        }
    }

    // Changes the spline funtions will work on
    [MenuItem("CONTEXT/Spline/Select As Working Spline")]
    public static void SelectCurrentSpline(MenuCommand mc) {

        Spline selected = mc.context as Spline;

        if (selected != null) {

            // A spline exists that is not managed, so add it
            if (!splines.Contains(selected.gameObject)) {

                splines.Add(selected.gameObject);
            }

            workingSpline = selected.gameObject;
        }
    }

    [MenuItem("CONTEXT/Spline/Add Point")]
    public static void AddSplinePointContext(MenuCommand mc) {

        SelectCurrentSpline(mc);
        AddSplinePoint();
    }
    

    /***** Singleton Classes for Editor Interaction *****/


    // Class that can get a line of text from the user using a popup window
    //class SplineSelector : ScriptableWizard {

    //    public void Select(string windowText) {

    //        ScriptableWizard.DisplayWizard<SplineSelector>("Select All of Component", "Make Selection");
    //    }

    //    private void OnWizardCreate() {

    //        Debug.Log("WINDOW CLOSED");
    //    }
    //}

    //class SplineSelector {

    //    int selected = 2;
    //    static string[] options = new string[] { "Option 0", "Option 1", "Option 2" };

    //    void OnGUI() {

    //        selected = GUILayout.SelectionGrid(selected, options, options.Length, EditorStyles.radioButton);
    //    }
    //}
}
