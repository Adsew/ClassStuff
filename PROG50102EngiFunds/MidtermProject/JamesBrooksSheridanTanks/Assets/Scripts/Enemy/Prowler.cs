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

            if (PlayerInLineOfSight()) {

                Quaternion cannonRot = cannon.transform.localRotation;
                Vector3 playerDirection = DirectionToPlayer();
                float xRotation = cannonRot.x;

                // Idea is to base rotation off distance and height difference between player and enemy
                float xDesiredRotation = ( Vector3.Magnitude(playerDirection) / 2.0f - (turret.transform.position.y - playerDirection.y + 20.0f) ) / 2.0f;
                
                playerDirection.y = 0;  // This tank turret head only rotates left-right

                // Turret rotation
                turret.transform.forward += rotationKH * (float)difficulty * (playerDirection.normalized - turret.transform.forward);

                // Cannon rotation
                xRotation += rotationKH * (xDesiredRotation - xRotation);

                if (xRotation > 60.0f) {

                    xRotation = 60.0f;
                }
                else if (xRotation < -30.0f) {

                    xRotation = -30.0f;
                }

                cannonRot.x = -xRotation;   // Negative angles upward
                cannon.transform.localRotation = cannonRot;

                if (PlayerInFiringRadius()) {

                    Fire();
                }
            }
            // Return to natural position
            else {

                Vector3 restingVec = body.transform.forward;
                Quaternion restingQuat = cannon.transform.localRotation;
                float xRotation = restingQuat.x;

                turret.transform.forward += rotationKH * (float)difficulty * (restingVec - turret.transform.forward);
                xRotation += rotationKH * (float)difficulty * (0.0f - xRotation);
                restingQuat.x = -xRotation;
                restingQuat.z = 0.0f;
                cannon.transform.localRotation = restingQuat;
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
        RotateTurretUpdate();

        HealthBarUpdate();
	}
}
