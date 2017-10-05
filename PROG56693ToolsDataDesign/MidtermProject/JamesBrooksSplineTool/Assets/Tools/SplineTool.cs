using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.Xml;
using System.Xml.Serialization;
using System.IO;

[InitializeOnLoad]
public class SplineTool {

    /*
     * THINGS TO IMPLEMENTS
     * 
     * Adding spline \
     * adding spline node to created spline  \
     * setting start of spline
     * loading splines back into tool on startup \
     * add context menu to gameobject right click in hierarchy
     * saveing loading splines to xml
     * Draw line with debug mode
     * Use some selecting to improve usability and visibility
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

    // Creates a new ,empty spline
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

    // Changes the spline that functions will operate on
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

    // Add point to the right-clicked spline
    [MenuItem("CONTEXT/Spline/Add Point")]
    public static void AddSplinePointContext(MenuCommand mc) {

        SelectCurrentSpline(mc);
        AddSplinePoint();
    }
    
    // Save all splines to an xml file
    [MenuItem("JB Tools/Spline/Save All Splines")]
    public static void SaveAllSplines() {

        SplineFileManager file = SplineFileManager.CreateInstance<SplineFileManager>();
        
        file.Save(splines);
    }

    // Save current spline to an xml file
    [MenuItem("JB Tools/Spline/Save Current Splines")]
    public static void SaveCurrentSpline() {

        List<GameObject> singleSpline = new List<GameObject>();
        singleSpline.Add(workingSpline);

        SplineFileManager file = SplineFileManager.CreateInstance<SplineFileManager>();

        file.Save(singleSpline);
    }


    /***** Classes for Editor Interaction and Serializing *****/
    
    // Single point in a spline
    [System.Serializable]
    public class SplinePointSerial {

        [XmlAttribute("Name")]
        public string name;

        [XmlAttribute("PosX")]
        public float x;

        [XmlAttribute("PosY")]
        public float y;

        [XmlAttribute("PosZ")]
        public float z;
    }

    // Properties of a spline
    [System.Serializable]
    public class SplineSerial {

        [XmlArray("Points"), XmlArrayItem("Point")]
        public SplinePointSerial[] points;

        [XmlAttribute("Name")]
        public string name;
        
        [XmlAttribute("Mode")]
        public Spline.GameModes gameMode;

        [XmlAttribute("Speed")]
        public float speed;
    }

    [XmlRoot("SplineSave")]
    public class SplineXmlObject {

        [XmlArray("Splines"), XmlArrayItem("Spline")]
        public SplineSerial[] splines;
    }

    // Class that can get a line of text from the user using a popup window
    // For saving and loading splines
    
    public class SplineFileManager : EditorWindow {

        public string fileName = "File.xml";

        public bool[] selected = null;
        public List<GameObject> splineList = null;
        
        public SplineSerial[] splinesToSave;

        private bool saveStarted = false;
        private bool loadStarted = false;

        public void Save(List<GameObject> sl) {

            int i = 0;

            saveStarted = true;
            splineList = sl;
            selected = new bool[splineList.Count];

            // Default true
            for (i = 0; i < selected.Length; i++) {

                selected[i] = true;
            }

            SplineFileManager window = (SplineFileManager)EditorWindow.GetWindow(typeof(SplineFileManager), true, "Save Splines to File");
            window.Show();
        }

        public void Load() {

            loadStarted = true;
            splineList = null;
            selected = null;

            SplineFileManager window = (SplineFileManager)EditorWindow.GetWindow(typeof(SplineFileManager), true, "Load Splines from File");
            window.Show();
        }

        private void OnGUI() {

            int i = 0, j = 0, k = 0;

            GUILayout.Label("File Name (include .xml):");
            fileName = EditorGUILayout.TextField(fileName);
            
            // Save Mode GUI items
            if (saveStarted) {
                
                bool somethingSelected = false;

                GUILayout.Label("Select Splines to Save:");

                for (i = 0; i < selected.Length; i++) {

                    if (splineList[i] != null) {

                        selected[i] = EditorGUILayout.Toggle(splineList[i].name, selected[i]);
                    }
                }

                // Only show save button if something selected
                for (i = 0; i < selected.Length; i++) {

                    if (selected[i] == true) {

                        somethingSelected = true;
                        break;
                    }
                }

                if (somethingSelected) {

                    if (GUILayout.Button("Save")) {

                        int numToSave = 0;

                        for (i = 0; i < selected.Length; i++) {

                            if (selected[i] == true) {

                                numToSave++;
                            }
                        }

                        splinesToSave = new SplineSerial[numToSave];

                        j = 0;  // Increment for each completed spline to save

                        // Construct spline data
                        for (i = 0; i < selected.Length; i++) {

                            if (selected[i] == true) {

                                Spline curSpline = splineList[i].GetComponent<Spline>();

                                if (curSpline != null) {

                                    splinesToSave[j] = new SplineSerial();
                                    splinesToSave[j].points = new SplinePointSerial[curSpline.contPoints.Count];
                                    
                                    splinesToSave[j].name = splineList[i].name;
                                    splinesToSave[j].gameMode = curSpline.gameMode;
                                    splinesToSave[j].speed = curSpline.speed;

                                    k = 0;

                                    foreach (GameObject p in curSpline.contPoints) {

                                        splinesToSave[j].points[k] = new SplinePointSerial();

                                        splinesToSave[j].points[k].name = p.name;
                                        splinesToSave[j].points[k].x = p.transform.position.x;
                                        splinesToSave[j].points[k].y = p.transform.position.y;
                                        splinesToSave[j].points[k].z = p.transform.position.z;

                                        k++;
                                    }

                                    j++;
                                }
                                else {

                                    Debug.Log("Error saving spline " + splineList[i].name + " to " + fileName + ".");

                                    splinesToSave[j].name = splineList[i].name;
                                    j++;
                                }
                            }
                        }

                        // Push to file
                        SplineXmlObject splineXML = new SplineXmlObject();
                        splineXML.splines = splinesToSave;
                        
                        var serializer = new XmlSerializer(typeof(SplineXmlObject));

                        using (var stream = new FileStream(fileName, FileMode.Create)) {

                            serializer.Serialize(stream, splineXML);
                        }

                        saveStarted = false;

                        this.Close();
                    }
                }
            }

            if (loadStarted) {

                if (GUILayout.Button("Load")) {

                    loadStarted = false;

                    this.Close();
                }
            }
        }
    }
}
