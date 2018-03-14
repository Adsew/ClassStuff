using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;
using UnityEngine.AI;

[NodeInfo(category = "NavMesh/Actions/")]
public class FollowPathAction : ActionNode {

    private NavMeshAgent agent;

    private int currentPoint;

    public WaypointContainer waypoints;

    public override void OnEnable() {

        base.OnEnable();
        
        agent = self.gameObject.GetComponent<NavMeshAgent>();

        currentPoint = 0;

        if (waypoints != null && waypoints.waypoints.Count > currentPoint) {

            agent.SetDestination(waypoints.waypoints[currentPoint].position);
        }
    }

    public override Status Update() {

        if (waypoints == null || waypoints.waypoints.Count == 0) {

            return Status.Failure;
        }

        if (agent.remainingDistance <= agent.stoppingDistance) {

            currentPoint = (currentPoint + 1) % waypoints.waypoints.Count;
            
            agent.SetDestination(waypoints.waypoints[currentPoint].position);
        }

        return Status.Running;
    }
}
