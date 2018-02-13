using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

public class BGhostRecallState : BGhostState {
    
    void OnEnable() {
        
        if (gControl != null) {

            gControl.moveToLocation = gControl.ReturnLocation;

            // Need to turn off or pacman will die touching eyes
            CircleCollider2D col = GetComponent<CircleCollider2D>();

            if (col != null) {

                col.enabled = false;
            }
        }
    }

    void Update() {

        if (gControl != null && myTrans != null) {

            if (myTrans.position.x == gControl.ReturnLocation.x
                && myTrans.position.y == gControl.ReturnLocation.y) {

                SendEvent("FINISHED");
            }
        }
    }
}
