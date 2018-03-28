using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using BehaviorDesigner.Runtime;
using BehaviorDesigner.Runtime.Tasks;

public class AgentAtDestinationCondition : Conditional {

    private NavMeshAgent agent = null;
    
    public override void OnAwake() {

        agent = GetComponent<NavMeshAgent>();
    }

    public override TaskStatus OnUpdate() {
        
        if (agent != null) {
            if (agent.remainingDistance <= agent.stoppingDistance) {

                return TaskStatus.Success;
            }
        }

        return TaskStatus.Failure;
    }
}
