using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

[CustomEditor(typeof(GraphNode))]
public class GraphCustomEditor : Editor
{
    private bool addReverseLink = false;
    private bool mShowList = true;

    public override void OnInspectorGUI()
    {
        //Draw all custons options
        GraphNode mySpline = (GraphNode)target;

        //Enable to add more than one control point
        ListAllAdjacentElements(mySpline);
    }

    private void ListAllAdjacentElements(GraphNode node)
    {
        node.removeLink(null);
        node.setDebug(GUILayout.Toggle(node.debug, "Debug"));
        node.setNodeColor(EditorGUILayout.ColorField("Node Color", node.nodeColor));
        node.setArrowColor(EditorGUILayout.ColorField("Arrow Color", node.arrowColor));

        //List all the control points of the spline
        mShowList = EditorGUILayout.Foldout(mShowList, "Adjacents");
        if (mShowList && node.adjacentNodes != null)
        {
            //list all node so you cna manage it
            for (int index = 0; index < node.adjacentNodes.Count; index++)
            {
                EditorGUILayout.BeginHorizontal();
                node.adjacentNodes[index] = (GameObject)EditorGUILayout.ObjectField(index + ":", node.adjacentNodes[index], typeof(GameObject), true);

                if (GUILayout.Button("Remove"))
                {
                    GameObject go = node.adjacentNodes[index];
                    node.adjacentNodes.RemoveAt(index);
                    if (go != null)
                    {
                        if (addReverseLink)
                        {
                            GraphNode gn = go.GetComponent<GraphNode>();
                            if (gn != null)
                            {
                                gn.removeLink(node.gameObject);
                            }
                        }
                    }
                }
                EditorGUILayout.EndHorizontal();
            }

            //Drag and drop link tool
            GameObject aux = (GameObject)EditorGUILayout.ObjectField("Add new link", null, typeof(GameObject), true);
            if (aux != null && aux != node.gameObject)
            {
                node.link(aux);

                GraphNode gn = aux.GetComponent<GraphNode>();
                if (gn == null)
                {
                    gn = aux.AddComponent<GraphNode>();
                }
                if (addReverseLink)
                {
                    gn.link(node.gameObject);
                }
            }
            if (aux == node.gameObject)
            {
                Debug.Log("You can`t link to yourself!");
            }

            //Add a new node and link it
            if (GUILayout.Button("Add"))
            {
                // ADD a new Node to your Graph
                string name = "Node_" + (node.gameObject.transform.parent.transform.childCount + 1).ToString("D3");
                GameObject go = new GameObject(name);
                go.transform.parent = node.gameObject.transform.parent;
                go.transform.position = node.gameObject.transform.position;
                GraphNode gn = go.AddComponent<GraphNode>();
                node.link(go);
                if (addReverseLink)
                {
                    gn.link(node.gameObject);
                }
                GameObject[] newSelection = new GameObject[1];
                newSelection[0] = go;
                Selection.objects = newSelection;
            }
        }
    }
}
