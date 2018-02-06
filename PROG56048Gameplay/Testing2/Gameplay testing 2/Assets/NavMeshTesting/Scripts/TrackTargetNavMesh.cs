using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class TrackTargetNavMesh : MonoBehaviour {

    private NavMeshAgent myAgent;
    private Animator myAnim;

    public Transform trackObj;
    public float v;

	// Use this for initialization
	void Start () {

        myAgent = GetComponent<NavMeshAgent>();
        myAnim = GetComponent<Animator>();
	}
	
    private void mouseClickUpdate() {

        if (Input.GetMouseButton(0)) {

            RaycastHit hit;

            if (Physics.Raycast(Camera.main.ScreenPointToRay(Input.mousePosition), out hit, 100)) {

                myAgent.SetDestination(hit.point);
            }
        }
    }

    private void navMeshTrackUpdate() {

        if (myAgent != null && myAnim != null && trackObj != null) {

            //float rotAngle = Vector3.Dot(gameObject.transform.forward, myAgent.destination - gameObject.transform.position);
            myAnim.SetFloat("Speed", Vector3.Magnitude(myAgent.velocity) / myAgent.speed);
            //myAnim.SetFloat("Rotation", rotAngle);
        }
    }

	// Update is called once per frame
	void Update () {

        mouseClickUpdate();
        navMeshTrackUpdate();
	}
}
