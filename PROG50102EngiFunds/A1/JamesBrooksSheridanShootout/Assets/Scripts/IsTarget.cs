using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class IsTarget : MonoBehaviour {
    
    /* Target Point Variables */

    protected bool hasBeenHit;
    protected int pointWorth;

    /* Life of Object Variables */

    public const float timeTilDeath = 5.0f;
    
    private bool needsToDie;
    private float deathTimer;
    
    // Must be called by any inheriting class in the start function
    protected void InitializeTarget() {

        hasBeenHit = false;

        needsToDie = false;
        deathTimer = 0;
    }

    protected void SendScoreUpdate(int value) {

        if (ScoreMgr.This != null) {

            ScoreMgr.This.IncScore(value);
        }
        else {

            Debug.Log("IsTarget: Can't update score. ScoreMgr does not exist.");
        }
    }

    // Destroy if target has been hit
    protected void determineDeath() {

        if (needsToDie) {

            deathTimer = deathTimer + Time.deltaTime;

            if (deathTimer > IsTarget.timeTilDeath) {

                Destroy(this.gameObject);
            }
        }
    }

    public void OnCollisionEnter(Collision col) {
        
        if (hasBeenHit == false) {
            
            hasBeenHit = true;
            needsToDie = true;

            // Only increase score if some player projectile hit it
            if (col.gameObject != null) {
                if (col.gameObject.GetComponent<IsProjectile>() != null) {
                    
                    SendScoreUpdate(pointWorth);
                }
            }
        }
    }
}
