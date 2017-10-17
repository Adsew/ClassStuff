using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Predator : Enemy {
    
    private GameObject propeller;

    public int baseHealth = 10;
    public int baseDamage = 1;

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

        if (propeller == null) {

            IsPropeller temp = this.gameObject.GetComponentInChildren<IsPropeller>();

            if (temp != null) {

                propeller = temp.gameObject;
            }
        }

        if (bulletSpawnLoc == null) {

            bulletSpawnLoc = this.gameObject.GetComponentInChildren<IsSpawnLocCannon>();
        }

        if (baseHealth <= 0) {

            baseHealth = 10;
        }

        difficulty = EnemySpawnMgr.This.DetermineDifficulty();
        maxHealth = baseHealth * difficulty;
        currentHealth = maxHealth;

        damage = baseDamage * difficulty;
    }

    override protected void RotateTurretUpdate() {

        if (turret != null && body != null) {

            if (PlayerInLineOfSight()) {

                Vector3 playerDirection = DirectionToPlayer();
                
                turret.transform.forward += rotationKH * (float)difficulty * (playerDirection.normalized - turret.transform.forward);
            }
            // Return to natural position
            else {

                Vector3 restingVec = new Vector3(0.0f, -0.5f, 0.0f);
                restingVec = body.transform.forward + restingVec;
                
                turret.transform.forward += rotationKH * (float)difficulty * (restingVec - turret.transform.forward);
            }
        }
    }

    private void propellerSpinUpdate() {

        if (propeller != null) {

            propeller.gameObject.transform.Rotate(Vector3.up, 10);
        }
    }

	// Update is called once per frame
	void Update () {

        propellerSpinUpdate();
        RotateTurretUpdate();
	}
}
