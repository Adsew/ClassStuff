using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class NavMeshSimpleMovement : MonoBehaviour {

    private NavMeshAgent agent = null;
    
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
            }
        }
	}
}
