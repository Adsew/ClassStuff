using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

public class SelectAllTag : ScriptableWizard {

    public string searchTag = "Tag to find";
    
    [MenuItem("GDAP/Search For Objects With Tag")]
    static void selectAllOfTag()
    {
        Debug.Log("Select is working");

        ScriptableWizard.DisplayWizard<SelectAllTag>("Select All of Tag", "Make Selection");
    }

    private void OnWizardCreate()
    {
        //unity engine function

        bool found = false;

        Debug.Log("Wizard Created");

        // This is supposed to seelct all game objects with tiype tag

        foreach (string s in UnityEditorInternal.InternalEditorUtility.tags)
        {
            if (s.CompareTo(searchTag) == 0)
            {
                GameObject[] gos = GameObject.FindGameObjectsWithTag(searchTag);
                
                Selection.objects = gos;

                found = true;
            }
        }

        if (!found)
        {
            Debug.Log(searchTag + " is not in tag list.");

            Selection.objects = new GameObject[0];
        }
    }
}
