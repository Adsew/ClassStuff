using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

[RequireComponent(typeof(NavMeshAgent))]
[RequireComponent(typeof(Animator))]
public class NPCMovementAnim : MonoBehaviour, IAnimComplete {

    private Animator anim;
    private NavMeshAgent agent;

    public Transform target;
    public float angularDampeningTime = 5.0f;
    public float deadZone = 10.0f;

    public enum States {

        Idle,
        Walking,
        Climbing,
        Jumping
    }
    public States state = States.Idle;

    // Use this for initialization
    void Start() {

        anim = GetComponent<Animator>();
        agent = GetComponent<NavMeshAgent>();

        if (agent != null) {

            agent.SetDestination(target.position);
        }
        
        deadZone *= Mathf.Deg2Rad;
    }

    // Update is called once per frame
    void Update() {

        if (agent.isOnOffMeshLink && state == States.Walking) {

            state = States.Climbing;
            anim.SetTrigger("Climbing");
        }

        switch (state) {

            case States.Idle: {


                }
                break;

            case States.Walking: {

                    if (agent != null && target != null) {

                        agent.SetDestination(target.position);

                        if (anim != null) {

                            // Calc speed
                            float speed = 0.0f;

                            if (agent.desiredVelocity != Vector3.zero) {

                                speed = Vector3.Project(agent.desiredVelocity, Vector3.forward).magnitude * agent.speed;
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
                break;

            case States.Climbing: {


                }
                break;

            case States.Jumping: {


                }
                break;
        }
    }

    private void OnAnimatorMove() {

        switch (state) {

            case States.Walking:
                agent.velocity = anim.deltaPosition / Time.deltaTime;
                break;

            case States.Climbing:
                transform.position = anim.rootPosition;
                break;
        }
    }

    public void AnimationCompleted() {

        agent.CompleteOffMeshLink();
        agent.isStopped = false;
    }
}
