using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

public class BInkyChaseState : BGhostChaseState {

    protected List<PelletController> pellets;

    public int changeStratAtXPellets = 7;

    new protected void Awake() {

        base.Awake();

        pellets = new List<PelletController>(Object.FindObjectsOfType<PelletController>());
    }

    new protected void Update() {

        // Inky will go wherever there are pallets left to try and beat the player to it
        if (gControl != null && pellets.Count > changeStratAtXPellets) {

            if (myTrans.position.x >= gControl.moveToLocation.x - 1 && myTrans.position.x <= gControl.moveToLocation.x + 1
                && myTrans.position.y >= gControl.moveToLocation.y - 1 && myTrans.position.y <= gControl.moveToLocation.y + 1) {

                int randPellet = 0;

                do {

                    if (pellets[randPellet] == null) {

                        pellets.RemoveAt(randPellet);
                    }

                    randPellet = (int)(Random.value * pellets.Count);

                } while (pellets[randPellet] == null && pellets.Count > 0);

                if (pellets.Count > 0) {

                    Vector3 nextLocation = pellets[randPellet].transform.localPosition;

                    gControl.moveToLocation.x = nextLocation.x;
                    gControl.moveToLocation.y = nextLocation.y + 1; // Pellet locations are 1 lower than actual location
                }
            }
        }
        else if (gControl != null) {

            gControl.moveToLocation = gControl.PacMan.position;
        }

        base.Update();
    }
}
