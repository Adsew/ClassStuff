using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner.Runtime.Tasks;

public class CanAttack : Conditional
{

    public AttackController attackController;

    public override TaskStatus OnUpdate()
    {
        if (attackController != null)
        {
            return attackController.CanAttack ? TaskStatus.Success : TaskStatus.Failure;
        }
        return TaskStatus.Failure;
    }
}
