using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

public class SelectAllComponent : ScriptableWizard {

    public string searchComp = "Component to find";
    public Component searchCompRef = null;

    [MenuItem("GDAP/Search For Objects With Component")]
    static void selectAllOfComponent()
    {
        Debug.Log("Select is working");

        ScriptableWizard.DisplayWizard<SelectAllComponent>("Select All of Component", "Make Selection");
    }

    private void OnWizardCreate()
    {
        //unity engine function
        bool found = false;

        Debug.Log("Wizard Created");

        // This is supposed to seelct all game objects with tiype from a component

        // Search by reference

        if(searchCompRef != null)
        {
            Component[] tempList = (Component [])GameObject.FindObjectsOfType(searchCompRef.GetType());
            List<GameObject> goList = new List<GameObject>();

            for (int i = 0; i < tempList.Length; i++)
            {
                goList.Add(tempList[i].gameObject);
            }

            Selection.objects = goList.ToArray();

            return;
        }


        // Search by name

        GameObject[] allObjects = GameObject.FindObjectsOfType<GameObject>();
        List<GameObject> gos = new List<GameObject>();
        
        foreach (GameObject go in allObjects)
        {
            if (go.GetComponent(searchComp) != null)
            {
                gos.Add(go);

                found = true;
            }
        }
        
        if (!found)
        {
            Debug.Log("No objects have " + searchComp);

            Selection.objects = new GameObject[0];
        }

        Selection.objects = gos.ToArray();
    }
}
