using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner.Runtime;
using BehaviorDesigner.Runtime.Tasks;

public class RemoveFromTransformList : Action {

    public SharedTransform toRemove;
    public SharedTransformList removeFrom;
    
    public override TaskStatus OnUpdate() {

        if (removeFrom.Value.Remove(toRemove.Value)) {

            return TaskStatus.Success;
        }

        return TaskStatus.Failure;
    }
}
