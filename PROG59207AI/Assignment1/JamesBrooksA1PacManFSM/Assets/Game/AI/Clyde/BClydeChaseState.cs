using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

public class BClydeChaseState : BGhostChaseState {

	new protected void Update() {

        if (gControl != null) {

            gControl.moveToLocation = gControl.PacMan.position;
        }

        base.Update();
    }
}
