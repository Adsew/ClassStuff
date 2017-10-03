using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

public class SplineCreator {

    /*
     * THINGS TO IMPLEMENTS
     * 
     * Adding spline
     * adding spline node to created spline
     * setting start of spline
     * loading splines back into tool on startup
     * saveing loading splines to xml
     * Draw line with debug mode
    */
    
    List<GameObject> splines;
    
    [MenuItem("JB Tools/Spline/New Spline")]
    public static void CreateNewSpline() {

        TextDialogueWindow window = new TextDialogueWindow();
        window.GetSingleText("New Spline Name");

        Debug.Log(name);

        //GameObject emptySpline = new GameObject("My spline");
        //emptySpline.AddComponent<Spline>();
    }


    /***** Singleton Classes for Editor Interaction *****/


    // Class that can get a line of text from the user using a popup window
    class TextDialogueWindow : ScriptableWizard {

        public string textField;

        public bool windowClosed;

        public void GetSingleText(string windowText) {

            ScriptableWizard.DisplayWizard<TextDialogueWindow>(windowText, "Accept");

            windowClosed = false;
            textField = "";
        }

        private void OnWizardCreate() {

            windowClosed = true;
        }
    }
}
