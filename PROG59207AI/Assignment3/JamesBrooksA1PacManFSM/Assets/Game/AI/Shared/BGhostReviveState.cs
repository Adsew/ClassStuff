using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

public class BGhostReviveState : BGhostState {
    
    private float cageTimer = 0.0f;

    public float timeTilRevive = 5.0f;

    void OnEnable() {

        cageTimer = 0.0f;
    }

    // OnStateUpdate is called on each Update frame between OnStateEnter and OnStateExit callbacks
    void Update() {

        cageTimer += Time.deltaTime;

        if (cageTimer >= timeTilRevive) {

            // Need to turn off or pacman will die touching eyes
            CircleCollider2D col = GetComponent<CircleCollider2D>();

            if (col != null) {

                col.enabled = true;
            }

            if (anim != null) {

                anim.SetBool("IsDead", false);
            }

            SendEvent("FINISHED");
        }
    }
}
