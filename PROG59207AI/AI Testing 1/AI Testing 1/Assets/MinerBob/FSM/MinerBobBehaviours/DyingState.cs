using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DyingState : StateMachineBehaviour {

    private MinerBob bob;

    public float timeTilDeletion = 5.0f;
    private float deathTimer = 0.0f;

    // OnStateEnter is called when a transition starts and the state machine starts to evaluate this state
    override public void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {

        bob = animator.GetComponent<MinerBob>();

        Debug.Log("Moving to " + this.GetType());
        
    }

    // OnStateUpdate is called on each Update frame between OnStateEnter and OnStateExit callbacks
    override public void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {

        deathTimer += Time.deltaTime;

        if (deathTimer >= timeTilDeletion) {

            animator.SetTrigger("DestroyMe");
        }
    }
}
