using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AstroidAction : Action {

    public GameObject toSpawn;

    override public void action() {

        if (toSpawn != null) {

            Transform myPlace = this.transform;

            for (int i = 0; i < 4; i++) {

                GameObject astroid = Instantiate(toSpawn);
                astroid.transform.SetPositionAndRotation(myPlace.position, myPlace.rotation);

                AstroidLogic move = astroid.GetComponent<AstroidLogic>();

                AstroidLogic initMove = gameObject.GetComponent<AstroidLogic>();

                if (move != null && initMove != null) {

                    if (i == 0) {

                        move.moveDir = new Vector3(0.1f, 0, 0) + initMove.moveDir;
                    }
                    if (i == 1) {

                        move.moveDir = new Vector3(-0.1f, 0, 0) + initMove.moveDir;
                    }
                    if (i == 2) {

                        move.moveDir = new Vector3(0, 0.1f, 0) + initMove.moveDir;
                    }
                    if (i == 3) {

                        move.moveDir = new Vector3(0, -0.1f, 0) + initMove.moveDir;
                    }
                }
            }
        }
    }
}
