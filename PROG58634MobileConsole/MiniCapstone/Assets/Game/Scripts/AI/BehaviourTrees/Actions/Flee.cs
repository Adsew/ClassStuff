using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner.Runtime;
using BehaviorDesigner.Runtime.Tasks;

public class Flee : Action {

	public SharedGameObject target;
    public SharedVector3 destination;
    public SharedFloat distance;

    public override TaskStatus OnUpdate()
    {
        if (target == null || target.Value == null || destination == null || distance == null)
        {
            return TaskStatus.Failure;
        }

        Vector3 dir = gameObject.transform.position - target.Value.transform.position;

        dir = dir.normalized;

        destination.Value = gameObject.transform.position + (dir * distance.Value);

        return TaskStatus.Success;
    }
}
