using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BGhostReviving : StateMachineBehaviour {
    
    private float cageTimer = 0.0f;

    public float timeTilRevive = 5.0f;
    
    // OnStateUpdate is called on each Update frame between OnStateEnter and OnStateExit callbacks
    override public void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {

        cageTimer += Time.deltaTime;

        if (cageTimer >= timeTilRevive) {

            // Need to turn off or pacman will die touching eyes
            CircleCollider2D col = animator.GetComponent<CircleCollider2D>();

            if (col != null) {

                col.enabled = true;
            }

            animator.SetBool("IsDead", false);
        }
    }
}
