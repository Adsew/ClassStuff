using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DestroyState : StateMachineBehaviour {

    private MinerBob bob;
    
    // OnStateEnter is called when a transition starts and the state machine starts to evaluate this state
    override public void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {

        bob = animator.GetComponent<MinerBob>();

        Destroy(bob.gameObject);
    }
}
