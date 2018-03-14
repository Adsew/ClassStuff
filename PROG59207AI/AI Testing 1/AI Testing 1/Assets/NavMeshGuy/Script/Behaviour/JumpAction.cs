using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;
using UnityEngine.AI;

[NodeInfo(category = "NavMesh/Actions/")]
public class JumpAction : ActionNode {

    private NavMeshAgent agent;
    private JumpCurve curve;

    private float currentJumpTime;

    public FloatVar jumpDuration;

    public override void Start() {
        
        agent = self.gameObject.GetComponent<NavMeshAgent>();
        curve = agent.currentOffMeshLinkData.offMeshLink.GetComponent<JumpCurve>();

        currentJumpTime = 0.0f;
    }

    public override Status Update() {


        if (currentJumpTime <= jumpDuration.Value) {

            Vector3 position = curve.getPosition(currentJumpTime, jumpDuration.Value);

            agent.transform.position = position;

            currentJumpTime += Time.deltaTime;

            return Status.Running;
        }

        agent.CompleteOffMeshLink();
        agent.isStopped = false;

        return Status.Success;
    }
}
