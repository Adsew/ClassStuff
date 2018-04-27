using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner.Runtime;
using BehaviorDesigner.Runtime.Tasks;

public class Wander : Action {

    public SharedVector3 position;
    public SharedGameObject avoidTarget;
    public SharedVector2 distanceRangeFromTarget;
    public SharedFloat searchRadius;

    public override TaskStatus OnUpdate()
    {
        if (position == null || avoidTarget == null || avoidTarget.Value == null || distanceRangeFromTarget == null || searchRadius == null)
        {
            return TaskStatus.Failure;
        }

        Vector3 wanderRadius = new Vector3(Random.Range(-1.0f, 1.0f),
                                                  0.0f,
                                                  Random.Range(-1.0f, 1.0f));
        wanderRadius.Normalize();
        wanderRadius = wanderRadius * searchRadius.Value;

        float distanceBehind = Random.Range(distanceRangeFromTarget.Value.x, distanceRangeFromTarget.Value.y);

        position.Value = avoidTarget.Value.transform.position + (-avoidTarget.Value.transform.right * distanceBehind) + wanderRadius;
        
        return TaskStatus.Success;
    }
}
