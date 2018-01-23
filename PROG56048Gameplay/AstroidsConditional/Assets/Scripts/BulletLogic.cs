using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletLogic : MonoBehaviour {

    private float dt = 0;
    private float timeTilDeath = 3.0f;

    public float speed;

	// Use this for initialization
	void Start () {
		
	}
    
    // Update is called once per frame
    void Update () {

        movementUpdate();
        deathTimerUpdate();
	}

    public void movementUpdate() {

        transform.position += transform.up * speed;
    }

    private void deathTimerUpdate() {

        dt += Time.deltaTime;

        if (dt >= timeTilDeath) {

            Destroy(gameObject);
        }
    }
}
