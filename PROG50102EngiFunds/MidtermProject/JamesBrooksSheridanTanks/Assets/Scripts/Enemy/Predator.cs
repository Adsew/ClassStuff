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

            bulletSpawnLoc = this.gameObject.GetComponentInChildren<IsSpawnLocMachinegun>();
        }

        if (baseHealth <= 0) {

            baseHealth = 10;
        }

        needsToDie = false;

        difficulty = EnemySpawnMgr.This.DetermineDifficulty();
        maxHealth = baseHealth * difficulty;
        currentHealth = maxHealth;

        damage = baseDamage * difficulty;
        timeBetweenShots = 0.4f;

        score = 5;
    }

    protected override void RotateTurretUpdate() {

        if (turret != null && body != null && needsToDie == false) {

            if (PlayerInLineOfSight()) {
                
                Vector3 playerDirection = DirectionToPlayer();
                
                // Rotate turret head
                turret.transform.forward += rotationKH * (float)difficulty * (playerDirection.normalized - turret.transform.forward);
                
                if (PlayerInFiringRadius()) {

                    Fire();
                }
            }
            // Return to natural position
            else {

                Vector3 restingVec = new Vector3(0.0f, -0.5f, 0.0f);
                restingVec = body.transform.forward + restingVec;
                
                turret.transform.forward += rotationKH * (float)difficulty * (restingVec - turret.transform.forward);
            }
        }
    }

    protected override void Fire() {

        if (bulletSpawnLoc != null) {

            if ((GameStateMgr.This.gameTime - timeLastShot) >= timeBetweenShots) {
                
                ((IsSpawnLocMachinegun)bulletSpawnLoc).SpawnObject();

                timeLastShot = GameStateMgr.This.gameTime;
            }
        }
        else {

            Debug.Log("Predator: Has no bullet spawn location to fire.");
        }
    }

    protected override void OnDeath() {

        // Make it fall apart on death
        Destroy(this.gameObject.GetComponent<Rigidbody>());
        body.AddComponent<Rigidbody>();
        turret.AddComponent<Rigidbody>();
        propeller.AddComponent<Rigidbody>();
    }

    private void propellerSpinUpdate() {

        if (propeller != null) {

            propeller.gameObject.transform.Rotate(Vector3.up, 10);
        }
    }
    
    // Update is called once per frame
    void Update () {

        DetermineDeath();
        propellerSpinUpdate();
        RotateTurretUpdate();
	}
}
