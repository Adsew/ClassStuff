using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Mining : StateMachineBehaviour {

    public float thirstIncrease;
    public float goldIncrease;
    public float fatigueIncrease;
    public float yearsSpent;

    private MinerBob bob;

    // OnStateEnter is called when a transition starts and the state machine starts to evaluate this state
    override public void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {

        bob = animator.GetComponent<MinerBob>();

        Debug.Log("Moving to " + this.GetType());
    }

    // OnStateUpdate is called on each Update frame between OnStateEnter and OnStateExit callbacks
    override public void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {

        Debug.Log("You mined an hour");

        bob.mine(goldIncrease, fatigueIncrease, thirstIncrease);
        bob.age(yearsSpent);

        if (bob.currentAge > bob.lifeSpan) {

            animator.SetTrigger("Dying");
        }
        else if (bob.currentGold >= bob.maxNuggets) {

            animator.SetTrigger("Deposit");
        }
        else if (bob.thirstLevel >= bob.thirstThreshold) {

            animator.SetTrigger("Thirsty");
        }
    }
}
