using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner.Runtime.Tasks;
using BehaviorDesigner.Runtime;

public class CalculateTargetOffset : Action
{
    public SharedGameObject Target;
    public SharedVector3 OffsetPosition;
    public float Offset = 1.0f;

    public override TaskStatus OnUpdate()
    {
        if (Target == null || Target.Value == null || OffsetPosition == null)
        {
            return TaskStatus.Failure;
        }

        Vector3 dir = Target.Value.transform.right.normalized;

        dir = dir * Offset;

        OffsetPosition.Value = Target.Value.transform.position + dir;
        
        return TaskStatus.Success;
    }
}
