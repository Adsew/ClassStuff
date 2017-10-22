using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Enemy : MonoBehaviour {

    protected AudioSource audSrc;

    protected IsSpawnLoc bulletSpawnLoc;
    protected IsHealthbar healthBar;
    protected GameObject body;
    protected GameObject turret;

    protected int maxHealth;
    protected int currentHealth;

    protected int damage;
    protected float timeBetweenShots = 1.0f;
    protected float timeLastShot = 0.0f;

    protected int difficulty;

    protected int score = 0;

    protected float rotationKH = 0.01f;

    protected float deathTimer = 0.0f;
    protected float timeTilDeath = 5.0f;    // Seconds

    protected bool needsToDie = false;
    
    public Spline myPath = null;

    public float sightDegrees = 100.0f;        // Degrees
    public float sightDistance = 100.0f;       // Units
    public float firingDegrees = 20.0f;        // Degrees

    protected abstract void RotateTurretUpdate();

    protected abstract void HealthBarUpdate();

    protected abstract void Fire();

    protected abstract void OnDeath();

    protected Vector3 DirectionToPlayer() {

        Vector3 newVec = new Vector3();

        if (turret != null) {

            newVec = Player.This.pBodyGameObject.transform.position - turret.transform.position;
        }

        return newVec;
    }

    protected bool PlayerInLineOfSight() {

        if (turret != null) {

            Vector3 playerVector = DirectionToPlayer();

            RaycastHit losFinder;

            // Had to raise origin to avoid colliding with terrain when reycast draws along above the terrain in parallel
            bool hitSomething = Physics.Raycast(this.transform.position + Vector3.up * 5.0f, playerVector.normalized , out losFinder, Vector3.Magnitude(playerVector));
            
            if (Vector3.Magnitude(playerVector) <= sightDistance) {
                if (Mathf.Abs(Vector3.Angle(turret.transform.forward, playerVector)) < (sightDegrees / 2.0f)) {
                    if (!hitSomething
                        || (hitSomething && losFinder.collider.gameObject == Player.This.pGameObject)) {

                        return true;
                    }
                }
            }
        }

        return false;
    }

    protected bool PlayerInFiringRadius() {

        if (turret != null) {

            Vector3 playerVector = DirectionToPlayer();

            if (Vector3.Magnitude(playerVector) <= sightDistance) {
                if (Mathf.Abs(Vector3.Angle(turret.transform.forward, playerVector)) < (firingDegrees / 2.0f)) {

                    return true;
                }
            }
        }

        return false;
    }

    // Call on every update of derived classes
    protected void DetermineDeath() {

        if (needsToDie) {

            deathTimer = deathTimer + Time.deltaTime;

            if (deathTimer > timeTilDeath) {
                
                Destroy(this.gameObject);
            }
        }
    }
    
    public void OnCollisionEnter(Collision c) {

        IsProjectile proj = c.gameObject.GetComponent<IsProjectile>();
        
        if (proj != null) {

            currentHealth -= proj.damage;

            if (SoundMgr.This.InEarshotOfPlayer(this.gameObject.transform.position)) {

                SoundMgr.This.PlayRandomCollisionSound(audSrc);
            }
            
            if (currentHealth <= 0) {

                currentHealth = 0;

                if (needsToDie == false) {

                    needsToDie = true;

                    if (myPath != null) {

                        myPath.RemoveHead(this.gameObject);
                    }

                    EnemySpawnMgr.This.RemoveDeadEnemy(this);
                    ScoreMgr.This.IncScore(score);

                    OnDeath();
                }
            }
        }
    }
}
