using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class NavMeshSimpleMovement : MonoBehaviour {

    private NavMeshAgent agent = null;

    // Patrol Variables
    private int routeDestination = 0;
    public bool patrolMode = true;
    public List<GameObject> patrolRoute = new List<GameObject>();
    
	// Use this for initialization
	void Start () {

        agent = GetComponent<NavMeshAgent>();
	}
	
	// Update is called once per frame
	void Update () {
		
        if (agent != null) {

            if (Input.GetMouseButton(0)) {

                Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
                RaycastHit hit;

                if (Physics.Raycast(ray, out hit, 100)) {

                    agent.SetDestination(hit.point);
                }

                patrolMode = false;
            }

            if (patrolRoute.Count > 0 && agent.velocity == Vector3.zero) {

                agent.SetDestination(patrolRoute[routeDestination].transform.position);
                routeDestination = (routeDestination + 1) % patrolRoute.Count;
            }
        }
	}
}
