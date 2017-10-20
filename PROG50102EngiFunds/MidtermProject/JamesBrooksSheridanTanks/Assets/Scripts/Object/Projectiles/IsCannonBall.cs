using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsCannonBall : IsProjectile {

    public int cannonBallVelocity = 20;

	// Use this for initialization
	void Start () {

        Rigidbody temp = null;

        InitProjectile();

        // Give cannon ball initial velocity specific to a cannon ball
        temp = this.gameObject.GetComponent<Rigidbody>();
        
        if (temp == null) {

            temp = this.gameObject.AddComponent<Rigidbody>();
        }

        temp.velocity = cannonBallVelocity * this.gameObject.transform.forward;
        
        timeTilDeath = 0.0f;    // Instant removal on collision
    }

    private new void OnCollisionEnter(Collision col) {

        CollisionOccurred(col);
    }

    // Update is called once per frame
    void Update () {

        determineDeath();
	}
}
