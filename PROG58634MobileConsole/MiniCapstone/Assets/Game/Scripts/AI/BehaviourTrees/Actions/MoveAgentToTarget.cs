using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using BehaviorDesigner.Runtime;
using BehaviorDesigner.Runtime.Tasks;

public class MoveAgentToTarget : Action
{
    public SharedGameObject target;
    public SharedVector3 position;
    private NavMeshAgent agent;

    public override void OnAwake()
    {
        agent = GetComponent<NavMeshAgent>();
    }

    public override TaskStatus OnUpdate()
    {
        if (target.Value != null && agent != null)
        {
            agent.SetDestination(target.Value.transform.position);

            return TaskStatus.Success;
        }
        else if (position != null && agent != null)
        {
            agent.SetDestination(position.Value);

            return TaskStatus.Success;
        }

        return TaskStatus.Failure;
    }
}
