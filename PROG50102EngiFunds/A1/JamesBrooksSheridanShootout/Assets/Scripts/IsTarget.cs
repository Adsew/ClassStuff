using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class IsTarget : MonoBehaviour {

    // GIVE ACCESS TO SCORE BOARD

    protected bool hasBeenHit;
    protected int pointWorth;    // Point worth of a target
    
    // Must be called by any inheriting class in the start function
    protected void InitializeTarget() {

        hasBeenHit = false;
    }

    protected void SendScoreUpdate(int value) {

        // Send given score to board blab la
    }

    public void OnCollisionEnter(Collision col) {

        if (hasBeenHit == false) {

            SendScoreUpdate(pointWorth);
            hasBeenHit = true;
        }
    }
}
