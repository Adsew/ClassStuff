using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IAnimCompleteBehaviour : StateMachineBehaviour {

    // OnStateExit is called when a transition ends and the state machine finishes evaluating this state
    override public void OnStateExit(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {

        IAnimComplete callback = animator.gameObject.GetComponent(typeof(IAnimComplete)) as IAnimComplete;

        if (callback != null) {

            callback.AnimationCompleted();
        }
    }
}
