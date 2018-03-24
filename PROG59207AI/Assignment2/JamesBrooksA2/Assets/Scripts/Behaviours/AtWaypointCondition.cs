using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using BehaviorDesigner.Runtime.Tasks;

public class AtWaypointCondition : Conditional {

    private NavMeshAgent agent = null;

    public override void OnAwake() {

        agent = GetComponent<NavMeshAgent>();
    }

    public override TaskStatus OnUpdate() {
        
        if (agent != null) {
            if (agent.desiredVelocity.magnitude == 0.0f) {

                return TaskStatus.Success;
            }
        }

        return TaskStatus.Failure;
    }
}
