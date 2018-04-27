using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner.Runtime.Tasks;
using BehaviorDesigner.Runtime;

public class SetVector3GameObject : Action {

    public SharedGameObject Value;
    public SharedVector3 Variable;

    public override TaskStatus OnUpdate()
    {
        if (Value == null || Value.Value == null || Variable == null)
        {
            return TaskStatus.Failure;
        }

        Variable.Value = Value.Value.transform.position;

        return TaskStatus.Success;
    }
}
