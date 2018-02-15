using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

public class BInkyChaseState : BGhostChaseState {

    protected PelletController[] pellets;

    new protected void Awake() {

        base.Awake();

        pellets = Object.FindObjectsOfType<PelletController>();
    }

    new protected void Update() {

        // Inky will go wherever there are pallets left to try and beat the player to it
        if (gControl != null) {



            gControl.moveToLocation = gControl.PacMan.position;
        }

        base.Update();
    }
}
