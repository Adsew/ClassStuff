using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner.Runtime;
using BehaviorDesigner.Runtime.Tasks;

public class RotateToPlayer : Action {

    public SharedGameObject target;
    public SharedFloat cutoffAngle;

    public override TaskStatus OnUpdate()
    {
        if (target == null || target.Value == null || cutoffAngle == null)
        {
            return TaskStatus.Failure;
        }

        Vector3 dir = target.Value.transform.position - gameObject.transform.position;
        dir.y = 0;
        dir = dir.normalized;

        if (Vector3.Angle(gameObject.transform.forward, dir) > cutoffAngle.Value)
        {
            gameObject.transform.rotation = Quaternion.Lerp(gameObject.transform.rotation, Quaternion.LookRotation(dir, Vector3.up), Time.deltaTime);
            return TaskStatus.Running;
        }

        gameObject.transform.forward = dir;

        return TaskStatus.Success;
    }
}
