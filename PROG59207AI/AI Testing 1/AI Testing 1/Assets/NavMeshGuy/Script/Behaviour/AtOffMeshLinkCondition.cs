using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;
using UnityEngine.AI;

[NodeInfo(category = "NavMesh/Conditions/")]
public class AtOffMeshLinkCondition : ConditionNode {

    private NavMeshAgent agent;

    public override void OnEnable() {

        base.OnEnable();

        agent = self.gameObject.GetComponent<NavMeshAgent>();
    }

    public override Status Update() {
        
        if (agent == null) {

            return Status.Error;
        }

        if (agent.isOnOffMeshLink) {

            return Status.Success;
        }

        return Status.Failure;
    }
}
