using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner.Runtime.Tasks;

public class TriggerAnimation : Action {

    private Animator anim = null;

    public string triggerName;

    public override void OnAwake() {
        
        anim = GetComponent<Animator>();
    }

    public override TaskStatus OnUpdate() {

        if (anim != null) {

            anim.SetTrigger(triggerName);
        }

        return TaskStatus.Success;
    }
}
