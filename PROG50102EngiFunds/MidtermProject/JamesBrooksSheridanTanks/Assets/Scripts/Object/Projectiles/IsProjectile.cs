using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsProjectile : MonoBehaviour {

    private float deathTimer;
    private bool needsToDie;

    protected float timeTilDeath = 5.0f;    // Seconds

    public int damage { get; protected set; }

    // Use this for initialization
    void Start () {

        InitProjectile();

        damage = 1;
	}

    protected void InitProjectile() {

        deathTimer = 0;
        needsToDie = false;
    }

    protected void CollisionOccurred(Collision col) {

        needsToDie = true;
    }

    // Default
    public void OnCollisionEnter(Collision col) {

        CollisionOccurred(col);
    }
    
    // Destroy bullet if it has hit something
    protected void determineDeath() {

        if (needsToDie) {

            deathTimer = deathTimer + Time.deltaTime;

            if (deathTimer > timeTilDeath) {

                Destroy(this.gameObject);
            }
        }
    }

    // Update is called once per frame
    void Update () {

        determineDeath();
	}
}
