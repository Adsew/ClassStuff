using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner.Runtime.Tasks;
using BehaviorDesigner.Runtime;

public class ConeOfSight : Conditional
{
    public SharedGameObjectList gameObjectsInCone;

    public override TaskStatus OnUpdate()
    {
        if (gameObjectsInCone != null && gameObjectsInCone.Value.Count > 0)
        {
            return TaskStatus.Success;
        }

        return TaskStatus.Failure;
    }
}
