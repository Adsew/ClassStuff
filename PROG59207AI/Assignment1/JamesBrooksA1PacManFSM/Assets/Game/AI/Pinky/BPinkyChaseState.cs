using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

public class BPinkyChaseState : BGhostChaseState {

    new protected void Update() {

        // Pinky will attempt to go where the player is trying to move
        if (gControl != null) {

            Vector2 pacmanFwd = new Vector2(0, 0);

            if (pacman.inputDirection == PacmanController.MoveDirection.Up) {

                pacmanFwd.y = -4.0f;
            }
            if (pacman.inputDirection == PacmanController.MoveDirection.Down) {

                pacmanFwd.y = 4.0f;
            }
            if (pacman.inputDirection == PacmanController.MoveDirection.Left) {

                pacmanFwd.x = -4.0f;
            }
            if (pacman.inputDirection == PacmanController.MoveDirection.Right) {

                pacmanFwd.x = 4.0f;
            }

            gControl.moveToLocation.x = gControl.PacMan.position.x + pacmanFwd.x;
            gControl.moveToLocation.y = gControl.PacMan.position.y + pacmanFwd.y;
        }

        base.Update();
    }
}
