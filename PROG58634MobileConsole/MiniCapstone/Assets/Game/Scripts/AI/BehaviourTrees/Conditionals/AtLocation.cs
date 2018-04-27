using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner.Runtime;
using BehaviorDesigner.Runtime.Tasks;

public class AtLocation : Conditional
{
    public SharedFloat threshold;
    public SharedGameObject target;
    public SharedVector3 destination;

    public override TaskStatus OnUpdate()
    {
        if (target != null && target.Value != null)
        {
            if (Vector3.Distance(transform.position, target.Value.transform.position) <= threshold.Value)
            {
                return TaskStatus.Success;
            }
        }
        else if (destination != null)
        {
            if (Vector3.Distance(transform.position, destination.Value) <= threshold.Value)
            {
                return TaskStatus.Success;
            }
        }

        return TaskStatus.Failure;
    }
}
