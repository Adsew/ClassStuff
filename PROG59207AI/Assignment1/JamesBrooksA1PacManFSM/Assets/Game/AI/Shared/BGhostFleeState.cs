using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

public class BGhostFleeState : BGhostState {

    private int currentDestination = 0;

    public List<Vector2> patrol;
    public float fleeDistance = 5.0f;

    private void OnEnable() {

        if (patrol.Count > 0) {

            currentDestination = currentDestination % patrol.Count; // Ensure destination is still within bounds

            gControl.moveToLocation = patrol[currentDestination];
        }
    }

    void Update() {
        
        if (myTrans != null && gControl != null) {

            // Run away if pacman is close
            if (Mathf.Abs(gControl.PacMan.position.x - myTrans.position.x) <= fleeDistance
                && Mathf.Abs(gControl.PacMan.position.y - myTrans.position.y) <= fleeDistance) {

                Vector2 dirVect;

                dirVect.x = myTrans.position.x - gControl.PacMan.position.x;
                dirVect.y = myTrans.position.y - gControl.PacMan.position.y;
                
                gControl.moveToLocation.x = myTrans.position.x + dirVect.x;
                gControl.moveToLocation.y = myTrans.position.y + dirVect.y;
            }

            // Do a general patrol if far enough away from pacman
            else if (patrol.Count > 0) {

                currentDestination = currentDestination % patrol.Count; // Ensure destination is still within bounds

                // Checking for in-range of next positoin avoids stop and waiting
                if (Mathf.Abs(myTrans.position.x - patrol[currentDestination].x) < 2.0f
                    && Mathf.Abs(myTrans.position.y - patrol[currentDestination].y) < 2.0f) {

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
