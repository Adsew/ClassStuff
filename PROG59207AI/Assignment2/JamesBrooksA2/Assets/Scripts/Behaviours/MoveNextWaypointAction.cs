using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using BehaviorDesigner.Runtime;
using BehaviorDesigner.Runtime.Tasks;

public class MoveNextWaypointAction : Action {

    private NavMeshAgent agent = null;
    private Animator anim = null;

    public string speedFloatName;

    public SharedInt waypointsPassed;

    public override void OnAwake() {

        agent = GetComponent<NavMeshAgent>();
        anim = GetComponent<Animator>();
    }

    public override TaskStatus OnUpdate() {

        if (agent != null && anim != null) {

            anim.SetFloat(speedFloatName, 0.5f);

            waypointsPassed.Value += 1;
        }

        return TaskStatus.Success;
    }
}
