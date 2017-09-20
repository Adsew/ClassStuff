using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsProjectile : MonoBehaviour {

    public const float deathTime = 10.0f;   // 10 Seconds after collision

    private float deathTimer;
    private bool needsToDie;

	// Use this for initialization
	void Start () {

        InitProjectile();
	}

    protected void InitProjectile() {

        deathTimer = 0;
        needsToDie = false;
    }

    public void OnCollisionEnter(Collision col) {

        // As long as we hit something, destroy object soon
        if (col.gameObject != null) {

            needsToDie = true;
        }
    }

    // Destroy bullet if it has hit something
    protected void determineDeath() {

        if (needsToDie) {

            deathTimer = deathTimer + Time.deltaTime;

            if (deathTimer > IsProjectile.deathTime) {

                Destroy(this.gameObject);
            }
        }
    }

    // Update is called once per frame
    void Update () {

        determineDeath();
	}
}
