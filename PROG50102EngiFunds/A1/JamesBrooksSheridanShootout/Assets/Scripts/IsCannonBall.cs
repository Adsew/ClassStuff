using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsCannonBall : IsProjectile {

    private const int cannonBallVelocity = 20;

	// Use this for initialization
	void Start () {

        Rigidbody temp = null;

        InitProjectile();

        // Give cannon ball initial velocity specific to a cannon ball
        temp = this.gameObject.GetComponent<Rigidbody>();
        
        if (temp != null) {

            temp.velocity = cannonBallVelocity * this.gameObject.transform.forward;
        }
	}
	
	// Update is called once per frame
	void Update () {

        determineDeath();
	}
}
