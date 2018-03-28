using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using BehaviorDesigner.Runtime;
using BehaviorDesigner.Runtime.Tasks;

public class RunToTarget : Action {

    private NavMeshAgent agent = null;
    private Animator anim = null;

    public SharedTransform target;
    public SharedTransformList sounds;

    public override void OnAwake() {

        agent = GetComponent<NavMeshAgent>();
        anim = GetComponent<Animator>();
    }

    public override TaskStatus OnUpdate() {

        if (anim != null && agent != null) {

            anim.SetFloat("Speed", 1.0f);

            Transform closestSpot = sounds.Value[0];
            float closestDistance = Vector3.Magnitude(transform.position - closestSpot.position);

            for (int i = 1; i < sounds.Value.Count; i++) {

                float dist = Vector3.Magnitude(transform.position - sounds.Value[i].position);

                if (dist < closestDistance) {

                    closestSpot = sounds.Value[i];
                    closestDistance = dist;
                }
            }

            target.Value = closestSpot;

            agent.SetDestination(target.Value.position);
        }

        return TaskStatus.Success;
    }
}
