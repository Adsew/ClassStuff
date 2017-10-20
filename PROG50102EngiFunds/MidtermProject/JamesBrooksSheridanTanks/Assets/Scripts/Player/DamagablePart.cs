using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DamagablePart : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}

    public void OnCollisionEnter(Collision c) {

        IsProjectile proj = c.gameObject.GetComponent<IsProjectile>();

        if (proj != null) {

            Player.This.takeDamage(proj.damage);
        }
    }

    // Update is called once per frame
    void Update () {
		
	}
}
