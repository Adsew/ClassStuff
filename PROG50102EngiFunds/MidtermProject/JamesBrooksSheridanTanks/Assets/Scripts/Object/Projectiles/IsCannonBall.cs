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
    }

    private new void OnCollisionEnter(Collision col) {

        collisionOccurred(col);

        if (SoundMgr.This.InEarshotOfPlayer(this.gameObject.transform.position)) {
            
            SoundMgr.This.PlayRandomCollisionSound();
        }
    }

    // Update is called once per frame
    void Update () {

        determineDeath();
	}
}
