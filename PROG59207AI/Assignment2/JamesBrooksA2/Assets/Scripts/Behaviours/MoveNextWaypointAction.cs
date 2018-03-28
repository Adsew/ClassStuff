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
    
    public SharedInt currentWaypoint;
    public SharedTransform waypointsParent;

    public SharedTransform destination;

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
            
            if (currentWaypoint.Value >= waypoints.Count) {

                currentWaypoint.Value = 0;
            }

            destination.Value = waypoints[currentWaypoint.Value];
            agent.SetDestination(waypoints[currentWaypoint.Value].position);
        }

        return TaskStatus.Success;
    }
}
