using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner.Runtime.Tasks;
using BehaviorDesigner.Runtime;

public class TriggerAttackEvent : Action
{
    public EventBehaviour eventBehaviour;
    public SharedGameObject eventGameObject;

    private readonly AttackEvent _attack = new AttackEvent();

    public override TaskStatus OnUpdate()
    {
        if (eventBehaviour != null)
        {
            _attack.Reset();
            _attack.attackGameObject = eventGameObject.Value;
            // TODO: add attack back in trigger attacks
            eventBehaviour.Handler.Invoke(_attack);
            return TaskStatus.Success;
        }
        Debug.LogError("EventBehaviour not set!");

        return TaskStatus.Failure;
    }
}
