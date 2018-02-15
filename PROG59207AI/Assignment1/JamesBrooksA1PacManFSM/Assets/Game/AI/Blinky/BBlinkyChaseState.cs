using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

public class BBlinkyChaseState : BGhostChaseState {

    new protected void Update() {

        // Blinky will stay behind where the player actually is, blocking retreat
        if (gControl != null) {

            Vector2 pacmanFwd = new Vector2(0, 0);

            if (pacman.moveDirection == PacmanController.MoveDirection.Up) {

                pacmanFwd.y = -4.0f;
            }
            if (pacman.moveDirection == PacmanController.MoveDirection.Down) {

                pacmanFwd.y = 4.0f;
            }
            if (pacman.moveDirection == PacmanController.MoveDirection.Left) {

                pacmanFwd.x = -4.0f;
            }
            if (pacman.moveDirection == PacmanController.MoveDirection.Right) {

                pacmanFwd.x = 4.0f;
            }

            gControl.moveToLocation.x = gControl.PacMan.position.x - pacmanFwd.x;
            gControl.moveToLocation.y = gControl.PacMan.position.y - pacmanFwd.y;
        }

        base.Update();
    }
}
