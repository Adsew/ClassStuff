using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class MouseMakeNoise : MonoBehaviour {

    private NavMeshAgent agent = null;
    private Animator anim = null;

    private float currentMaxSpeed = 0.5f;

    public float angularDampeningTime = 5.0f;
    public float deadZone = 10.0f;

    private void Start() {

        agent = GetComponent<NavMeshAgent>();
        anim = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update () {
		
        if (agent != null && anim != null) {

            if (Input.GetMouseButtonDown(0)){

                RaycastHit ray;

                if (Physics.Raycast(Camera.main.ScreenPointToRay(Input.mousePosition), out ray, 100)) {

                    agent.SetDestination(ray.point);

                    if (anim != null) {

                        // Calc speed
                        float speed = 0.0f;

                        if (agent.desiredVelocity != Vector3.zero) {

                            speed = currentMaxSpeed;
                        }

                        anim.SetFloat("Speed", speed);

                        // Find angle for rotation
                        float angle = Vector3.Angle(transform.forward, agent.desiredVelocity) * Mathf.Deg2Rad;

                        // Use deadzone to determine if rotation is needed
                        if (Mathf.Abs(angle) <= deadZone) {

                            transform.LookAt(transform.position + agent.desiredVelocity);
                        }
                        else {

                            transform.rotation = Quaternion.Lerp(
                                transform.rotation,
                                Quaternion.LookRotation(agent.desiredVelocity),
                                Time.deltaTime * angularDampeningTime
                                );
                        }
                    }
                }
            }

            if (agent.stoppingDistance >= (transform.position - agent.destination).magnitude) {

                anim.SetFloat("Speed", 0.0f);
            }
        }
	}

    private void OnAnimatorMove() {

        agent.velocity = anim.deltaPosition / Time.deltaTime;
    }
}
