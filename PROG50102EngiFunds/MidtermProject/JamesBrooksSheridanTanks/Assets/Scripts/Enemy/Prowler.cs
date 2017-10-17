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

        if (baseHealth <= 0) {

            baseHealth = 15;
        }

        difficulty = EnemySpawnMgr.This.DetermineDifficulty();
        maxHealth = baseHealth * difficulty;
        currentHealth = maxHealth;

        damage = baseDamage * difficulty;
    }

    override protected void RotateTurretUpdate() {

        if (turret != null && body != null && cannon != null) {

            if (PlayerInLineOfSight()) {

                Vector3 playerDirection = DirectionToPlayer();
                playerDirection.y = 0;  // This tank turret head only rotates left-right

                turret.transform.forward += rotationKH * (float)difficulty * (playerDirection.normalized - turret.transform.forward);
            }
            // Return to natural position
            else {

                Vector3 restingVec = body.transform.forward;

                turret.transform.forward += rotationKH * (float)difficulty * (restingVec - turret.transform.forward);
            }
        }
    }

    // Update is called once per frame
    void Update () {

        RotateTurretUpdate();
	}
}
