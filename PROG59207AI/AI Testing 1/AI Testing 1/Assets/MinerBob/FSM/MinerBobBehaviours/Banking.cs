using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Banking : StateMachineBehaviour {

    private MinerBob bob;

    // OnStateEnter is called when a transition starts and the state machine starts to evaluate this state
    override public void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {

        bob = animator.GetComponent<MinerBob>();

        Debug.Log("Moving to " + this.GetType());
    }

    // OnStateUpdate is called on each Update frame between OnStateEnter and OnStateExit callbacks
    override public void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {

        bob.deposit(bob.currentGold);

        if (bob.fatigueLevel > bob.tirednessThreshold) {

            animator.SetTrigger("Tired");
        }
        else {

            animator.SetTrigger("Rested");
        }
    }
}
