using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

//Graph tool
public class GraphsManagerTool : ScriptableWizard
{
    [MenuItem("Graph/New Graph")]
    static void createSpline()
    {
        //All spline configuration should be sone on Editor
        GameObject graph = new GameObject("Graph");
        GameObject node = new GameObject("Node_001");
        node.transform.parent = graph.transform;
        node.AddComponent<GraphNode>();
    }
}
