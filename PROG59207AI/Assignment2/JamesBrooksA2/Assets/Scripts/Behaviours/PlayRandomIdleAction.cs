using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using BehaviorDesigner.Runtime;
using BehaviorDesigner.Runtime.Tasks;

public class PlayRandomIdleAction : Action {
    
    private Animator anim = null;

    public string idlePlayTriggerName;
    public string idleToPlayName;
    public string idleCountVarName;

    public SharedInt waypointsPassed;

    public override void OnAwake() {
        
        anim = GetComponent<Animator>();
    }

    public override TaskStatus OnUpdate() {

        if (anim != null) {

            int idles = anim.GetInteger(idleCountVarName);
            int idleToPlay = Random.Range(0, idles - 1);

            anim.SetFloat(idleToPlayName, (float)idleToPlay);
            anim.SetTrigger(idlePlayTriggerName);
        }

        waypointsPassed.Value = 0;

        return TaskStatus.Success;
    }
}
