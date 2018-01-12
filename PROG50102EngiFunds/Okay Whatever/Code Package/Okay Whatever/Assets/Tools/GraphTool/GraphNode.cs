using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//This is the graph node
public class GraphNode : MonoBehaviour
{
    //List of adjacets nodes
    public List<GameObject> adjacentNodes = new List<GameObject>();
    public bool debug = true;
    public Color arrowColor = Color.blue;
    public Color nodeColor = Color.yellow;

    private const float SPHERE_RADIOUS = 0.3f;

    private int mLevel;
    private float mDist;
    private Vector3 mTarget;

    //Draw the Graph Representation
    void OnDrawGizmos()
    {
        if (debug)
        {
            Vector3 position = this.gameObject.transform.position;
            Gizmos.color = arrowColor;

            foreach (GameObject go in adjacentNodes)
            {
                if (go != null)
                {
                    drawArrow(position, (go.transform.position - position));
                }
            }
            Gizmos.color = nodeColor;

            Gizmos.DrawSphere(position, SPHERE_RADIOUS);
        }
    }

    public void setDebug(bool d)
    {
        if (d != debug)
        {
            debug = d;
            foreach (GameObject go in adjacentNodes)
            {
                if (go != null)
                {
                    GraphNode node = go.GetComponent<GraphNode>();
                    if (node != null)
                    {
                        node.setDebug(d);
                    }
                }
            }
        }
    }


    public void setNodeColor(Color c)
    {
        if (c != nodeColor)
        {
            nodeColor = c;
            foreach (GameObject go in adjacentNodes)
            {
                if (go != null)
                {
                    GraphNode node = go.GetComponent<GraphNode>();
                    if (node != null)
                    {
                        node.setNodeColor(c);
                    }
                }
            }
        }
    }

    public void setArrowColor(Color c)
    {
        if (c != arrowColor)
        {
            arrowColor = c;
            foreach (GameObject go in adjacentNodes)
            {
                if (go != null)
                {
                    GraphNode node = go.GetComponent<GraphNode>();
                    if (node != null)
                    {
                        node.setArrowColor(c);
                    }
                }
            }
        }
    }

    public void link(GameObject aux)
    {
        adjacentNodes.Add(aux);
    }

    public void removeLink(GameObject gameObject)
    {
        adjacentNodes.Remove(gameObject);
    }

    /**
     * Draw an arrow
     * reference used to create the code:
     *          https://forum.unity.com/threads/debug-drawarrow.85980/
     */
    public static void drawArrow(Vector3 pos, Vector3 direction, float arrowHeadLength = 1.0f, float arrowHeadAngle = 20.0f)
    {
        direction = direction * ((direction.magnitude - SPHERE_RADIOUS) / direction.magnitude);

        Gizmos.DrawRay(pos, direction);
        Vector3 right = Quaternion.LookRotation(direction) * Quaternion.Euler(0, 180 + arrowHeadAngle, 0) * new Vector3(0, 0, 1);
        Vector3 left = Quaternion.LookRotation(direction) * Quaternion.Euler(0, 180 - arrowHeadAngle, 0) * new Vector3(0, 0, 1);

        Vector3 right_2 = Quaternion.LookRotation(direction) * Quaternion.Euler(180 + arrowHeadAngle, 0, 0) * new Vector3(0, 0, 1);
        Vector3 left_2 = Quaternion.LookRotation(direction) * Quaternion.Euler(180 - arrowHeadAngle, 0, 0) * new Vector3(0, 0, 1);
        Gizmos.DrawRay(pos + direction, right * arrowHeadLength);
        Gizmos.DrawRay(pos + direction, left * arrowHeadLength);
        Gizmos.DrawRay(pos + direction, right_2 * arrowHeadLength);
        Gizmos.DrawRay(pos + direction, left_2 * arrowHeadLength);

    }

    public float getDist(int level, Vector3 targetPosition)
    {
        if (targetPosition == mTarget && level < mLevel)
        {
            return mDist;
        }

        float minDist;
        if (level == 0)
        {
            minDist = (adjacentNodes[0].transform.position - targetPosition).magnitude;
        }
        else
        {
            minDist = (adjacentNodes[0].transform.position - targetPosition).magnitude;
            foreach (GameObject adj in adjacentNodes)
            {
                GraphNode adjGraph = adj.GetComponent<GraphNode>();

                float dist = adjGraph.getDist(level - 1, targetPosition);
                dist += 0.01f;
                if (dist < minDist)
                {
                    minDist = dist;
                }
            }
        }

        mTarget = targetPosition;
        mLevel = level;
        mDist = minDist;

        return minDist;
    }

    public void resetDist()
    {
        if (mLevel != -1)
        {
            mLevel = -1;
            foreach (GameObject adj in adjacentNodes)
            {
                GraphNode adjGraph = adj.GetComponent<GraphNode>();
                adjGraph.resetDist();
            }
        }
    }
}