using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Prowler : Enemy {

    protected GameObject cannon;

    public int baseHealth = 15;
    public int baseDamage = 5;

    // Use this for initialization
    void Start () {

        if (body == null) {

            IsTankBody temp = this.gameObject.GetComponentInChildren<IsTankBody>();

            if (temp != null) {

                body = temp.gameObject;
            }
        }

        if (turret == null) {

            IsTurretHead temp = this.gameObject.GetComponentInChildren<IsTurretHead>();

            if (temp != null) {

                turret = temp.gameObject;
            }
        }

        if (cannon == null) {

            IsCannon temp = this.gameObject.GetComponentInChildren<IsCannon>();

            if (temp != null) {

                cannon = temp.gameObject;
            }
        }

        if (bulletSpawnLoc == null) {

            bulletSpawnLoc = this.gameObject.GetComponentInChildren<IsSpawnLocCannon>();
        }

        if (healthBar == null) {

            healthBar = this.gameObject.GetComponentInChildren<IsHealthbar>();
        }

        if (baseHealth <= 0) {

            baseHealth = 15;
        }

        if (audSrc == null) {

            audSrc = this.gameObject.AddComponent<AudioSource>();
            audSrc.playOnAwake = false;
            audSrc.volume = 0.7f;
        }

        needsToDie = false;

        difficulty = EnemySpawnMgr.This.DetermineDifficulty();
        maxHealth = baseHealth * difficulty;
        currentHealth = maxHealth;

        damage = baseDamage * difficulty;
        timeBetweenShots = 2.0f;

        firingDegrees = 30.0f;

        score = 1;
    }

    protected override void RotateTurretUpdate() {

        if (turret != null && body != null && cannon != null && needsToDie == false) {

            if (PlayerInLineOfSight() || recentlyHit) {

                Vector3 cannonRot = cannon.transform.localEulerAngles;
                Vector3 playerDirection = DirectionToPlayer();
                float xRotation = cannonRot.x;
                
                // Cannon needs to be in the perspective above and below 0
                if (xRotation > 180) {

                    xRotation -= 360.0f;
                }

                // Cannon rotation
                // Idea is to base rotation off distance and height difference between player and enemy
                float xDesiredRotation = -( Vector3.Magnitude(playerDirection) / 2.0f - (26.0f - playerDirection.y) ) / 2.0f;
                
                if (xDesiredRotation > 60.0f) {

                    xDesiredRotation = 60.0f;
                }
                else if (xDesiredRotation < -40.0f) {

                    xDesiredRotation = -30.0f;
                }
                
                xRotation += rotationKH * (xDesiredRotation - xRotation);
                
                // Put back into expected angles
                if (xRotation < 0.0f) {

                    xRotation += 360.0f;
                }
                
                cannon.transform.localEulerAngles = new Vector3(xRotation, 0.0f, 0.0f);

                // Turret rotation
                playerDirection.y = 0;  // This tank turret head only rotates left-right
                turret.transform.forward += rotationKH * (float)difficulty * (playerDirection.normalized - turret.transform.forward);

                if (PlayerInFiringRadius()) {

                    Fire();
                }
            }
            // Return to natural position
            else {

                Vector3 restingVec = body.transform.forward;
                Vector3 restingCanRot = cannon.transform.localEulerAngles;
                float xRotation = restingCanRot.x;

                turret.transform.forward += rotationKH * (float)difficulty * (restingVec - turret.transform.forward);

                xRotation += rotationKH * (0.0f - xRotation);
                
                cannon.transform.localEulerAngles = new Vector3(xRotation, 0.0f, 0.0f);
            }
        }
    }

    protected override void HealthBarUpdate() {

        healthBar.SetHealthPercent((float)currentHealth / (float)maxHealth);
    }

    protected override void Fire() {

        if (bulletSpawnLoc != null) {

            if ((GameStateMgr.This.gameTime - timeLastShot) >= timeBetweenShots) {

                IsProjectile temp = ((IsSpawnLocCannon)bulletSpawnLoc).SpawnObject();
                temp.damage = damage;

                timeLastShot = GameStateMgr.This.gameTime;
            }
        }
        else {

            Debug.Log("Prowler: Has no bullet spawn location to fire.");
        }
    }

    protected override void OnDeath() {

        // Make it fall apart on death
        Destroy(this.gameObject.GetComponent<Rigidbody>());
        body.AddComponent<Rigidbody>();
        turret.AddComponent<Rigidbody>();
        cannon.AddComponent<Rigidbody>();

        if (SoundMgr.This.InEarshotOfPlayer(this.gameObject.transform.position)) {

            SoundMgr.This.PlayRandomExplosionSound(audSrc);
        }
    }

    // Update is called once per frame
    void Update () {

        DetermineDeath();
        DeterminePursuit();

        RotateTurretUpdate();

        HealthBarUpdate();
	}
}
