using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SplineMoveOnGraph : MonoBehaviour
{
    public bool constantSpeed = true;
    public bool folowPlayer = false;
    public float t;
    public GameObject p1;
    public GameObject p2;
    public GameObject p3;
    public GameObject p4;

    [Range(0.0f, 0.3f)]
    public float dt = 0.1f;

    private Quaternion initialRoration;

    private void Start()
    {
        initialRoration = this.transform.rotation;
    }

    // Update is called once per frame
    void Update()
    {
        if (p4 != null)
        {
            UpdateMove();
        }
        if (p4 != null)
        {
            UpdatePosition();
        }
        else
        {
            AutoDestroy autoDestoy = gameObject.AddComponent<AutoDestroy>();
            autoDestoy.secondsToDestroy = 10.0f;
            Destroy(this);
            SendMessage("OnSplineEnded", SendMessageOptions.DontRequireReceiver);
        }
    }


    // Update the game object position
    private void UpdatePosition()
    {
        Vector3 pos = CatmullRom.getPosition(p1.transform.position, p2.transform.position, p3.transform.position, p4.transform.position, t);
        gameObject.transform.position = pos;
        gameObject.transform.rotation = initialRoration;
    }

    //Just increase the dt
    private void UpdateMove()
    {
        if (constantSpeed)
        {
            // Get the speed ona  point using the derivated function.
            // set dt according to the speed
            Vector3 tan = CatmullRom.getTangent(p1.transform.position, p2.transform.position, p3.transform.position, p4.transform.position, t);
            if (tan.magnitude == 0)
            {
                t = t + dt;
            }
            else
            {
                t = t + (dt / tan.magnitude);
            }
        }
        else
        {
            t = t + dt;
        }
        if (t > 1)
        {
            //find a new p4;
            p1 = p2;
            p2 = p3;
            p3 = p4;

            //Look into all nodes and decide which one to go
            GraphNode aux = p4.GetComponent<GraphNode>();
            if (aux != null)
            {
                List<GameObject> adjacentNodes = aux.adjacentNodes;
                if (folowPlayer && PlayerManager.Instance.activePlayer != null)
                {
                    Vector3 targetPosition = PlayerManager.Instance.activePlayer.transform.position;
                    GraphNode adjGraph = adjacentNodes[0].GetComponent<GraphNode>();
                    float minDist = adjGraph.getDist(10, targetPosition);
                    GameObject next = adjacentNodes[0];
                    foreach (GameObject adj in adjacentNodes)
                    {
                        adjGraph = adj.GetComponent<GraphNode>();
                        float dist = adjGraph.getDist(10, targetPosition);
                        if (dist < minDist)
                        {
                            minDist = dist;
                            next = adj;
                        }
                    }
                    p4 = next;

                    foreach (GameObject adj in adjacentNodes)
                    {
                        adjGraph = adj.GetComponent<GraphNode>();
                        adjGraph.resetDist();
                    }

                }
                else
                {
                    if (adjacentNodes != null && adjacentNodes.Count > 0)
                    {
                        // otherwise go to a random node
                        int index = Random.Range(0, adjacentNodes.Count);
                        //if it goes back try again
                        if (adjacentNodes[index] == p2)
                            index = Random.Range(0, adjacentNodes.Count);
                        p4 = adjacentNodes[index];
                    }
                    else
                    {
                        p4 = null;
                    }
                }
            }
        }

        t %= 1;
    }
}
