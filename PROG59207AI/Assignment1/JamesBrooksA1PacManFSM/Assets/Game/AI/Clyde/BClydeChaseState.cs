using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

public class BClydeChaseState : BGhostChaseState {

	new protected void Update() {

        // Clyde will chase by following the player directly
        if (gControl != null) {

            gControl.moveToLocation = gControl.PacMan.position;
        }

        base.Update();
    }
}
