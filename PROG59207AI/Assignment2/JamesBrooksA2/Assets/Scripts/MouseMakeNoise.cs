using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class MouseMakeNoise : MonoBehaviour {

    private NavMeshAgent agent = null;
    private Animator anim = null;
    
    void Start() {

        agent = GetComponent<NavMeshAgent>();
        anim = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update () {
		
        if (Input.GetMouseButtonDown(0)) {

            if (agent != null && anim != null) {

                RaycastHit ray;

                if (Physics.Raycast(Camera.main.ScreenPointToRay(Input.mousePosition), out ray, 100)) {
                    
                    
                }
            }
        }
	}

    private void OnAnimatorMove() {

        agent.velocity = anim.deltaPosition / Time.deltaTime;
    }
}
