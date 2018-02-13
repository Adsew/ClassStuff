using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

public class BGhostFleeState : BGhostState {

    private int currentDestination = 0;

    public List<Vector2> patrol;

    private void OnEnable() {

        if (patrol.Count > 0) {

            currentDestination = currentDestination % patrol.Count; // Ensure destination is still within bounds

            gControl.moveToLocation = patrol[currentDestination];
        }
    }

    void Update() {
        
        if (myTrans != null && gControl != null) {

            // Do a general patrol if far enough away from pacman
            if (patrol.Count > 0) {

                currentDestination = currentDestination % patrol.Count; // Ensure destination is still within bounds

                if (myTrans.position.x == patrol[currentDestination].x
                    && myTrans.position.y == patrol[currentDestination].y) {

                    currentDestination = (currentDestination + 1) % patrol.Count;

                    gControl.moveToLocation = patrol[currentDestination];
                }
            }

            // Transition to recall if killed by pacman
            if (anim.GetBool("IsDead")) {

                SendEvent("GHOST_DIED");
            }

            // Invincibility over, chase pacman again
            else if (state == GameDirector.States.enState_Normal) {

                SendEvent("CHASE_PACMAN");
            }
        }
    }
}
