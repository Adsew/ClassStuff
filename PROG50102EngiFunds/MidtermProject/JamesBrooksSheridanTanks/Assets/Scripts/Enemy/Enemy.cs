using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Enemy : MonoBehaviour {

    protected IsSpawnLocCannon bulletSpawnLoc;
    protected GameObject body;
    protected GameObject turret;

    protected int maxHealth;
    protected int currentHealth;

    protected int damage;

    protected int difficulty;

    protected float rotationKH = 0.01f;

    public float sightDegrees = 100.0f;        // Degrees
    public float sightDistance = 100.0f;       // Units

    abstract protected void RotateTurretUpdate();

    protected Vector3 DirectionToPlayer() {

        Vector3 newVec = new Vector3();

        if (turret != null) {

            newVec = Player.This.pGameObject.transform.position - turret.transform.position;
        }

        return newVec;
    }

    protected bool PlayerInLineOfSight() {

        if (turret != null) {

            Vector3 playerVector = DirectionToPlayer();

            if (Vector3.Magnitude(playerVector) <= sightDistance) {
                if (Mathf.Abs(Vector3.Angle(turret.transform.forward, playerVector)) < (sightDegrees / 2.0f)) {

                    return true;
                }
            }
        }

        return false;
    }
}
