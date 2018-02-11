using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BGhostRecall : StateMachineBehaviour {

    private GhostController gControl;
    private Transform myTrans;

    // OnStateEnter is called when a transition starts and the state machine starts to evaluate this state
    override public void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {

        gControl = animator.GetComponent<GhostController>();
        myTrans = animator.transform;

        if (gControl != null) {

            gControl.moveToLocation = gControl.ReturnLocation;

            // Need to turn off or pacman will die touching eyes
            CircleCollider2D col = animator.GetComponent<CircleCollider2D>();

            if (col != null) {

                col.enabled = false;
            }
        }
    }

    // OnStateUpdate is called on each Update frame between OnStateEnter and OnStateExit callbacks
    override public void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {

        if (gControl != null && myTrans != null) {

            if (myTrans.position.x == gControl.ReturnLocation.x 
                && myTrans.position.y == gControl.ReturnLocation.y) {

                animator.SetTrigger("IsHome");
            }
        }
    }
}
