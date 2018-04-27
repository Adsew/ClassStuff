using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner.Runtime;
using BehaviorDesigner.Runtime.Tasks;

public class IsDead : Conditional {

    private GameCharacter character;

    public override void OnAwake()
    {
        character = gameObject.GetComponent<GameCharacter>();
    }

    public override TaskStatus OnUpdate()
    {
        if (character != null)
        {
            if (character.Health <= 0)
            {
                return TaskStatus.Success;
            }
        }

        return TaskStatus.Failure;
    }
}
