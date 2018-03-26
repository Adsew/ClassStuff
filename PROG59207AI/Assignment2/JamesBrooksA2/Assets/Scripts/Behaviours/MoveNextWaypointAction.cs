using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using BehaviorDesigner.Runtime;
using BehaviorDesigner.Runtime.Tasks;

public class MoveNextWaypointAction : Action {

    private NavMeshAgent agent = null;
    private Animator anim = null;

    private List<Transform> waypoints = new List<Transform>();

    public string speedFloatName;

    public SharedInt waypointsPassed;
    public SharedInt currentWaypoint;
    public SharedTransform waypointsParent;

    public override void OnAwake() {

        agent = GetComponent<NavMeshAgent>();
        anim = GetComponent<Animator>();

        foreach (Transform trans in waypointsParent.Value) {

            waypoints.Add(trans);
        }
    }

    public override TaskStatus OnUpdate() {

        if (agent != null && anim != null) {

            // Move to next waypoint
            anim.SetFloat(speedFloatName, 0.5f);

            currentWaypoint.Value += 1;

            if (currentWaypoint.Value >= waypoints.Count) {

                currentWaypoint.Value = 0;
            }

            agent.SetDestination(waypoints[currentWaypoint.Value].position);

            waypointsPassed.Value += 1;
        }

        return TaskStatus.Success;
    }
}
