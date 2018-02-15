using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

public class BGhostChaseState : BGhostState {

    protected PacmanController pacman;

    new protected void Awake() {

        base.Awake();

        if (pacman == null && gControl != null) {

            pacman = gControl.PacMan.gameObject.GetComponent<PacmanController>();
        }
    }

    protected void Update() {
        
        // Check need to flee
        if (state == GameDirector.States.enState_PacmanInvincible) {

            SendEvent("FLEE_PACMAN");
        }

        // Check need to die and recall
        else if (anim.GetBool("IsDead")) {

            SendEvent("GHOST_DIED");
        }
    }
}
