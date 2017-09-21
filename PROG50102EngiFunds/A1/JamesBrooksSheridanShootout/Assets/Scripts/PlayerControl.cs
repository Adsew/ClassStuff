using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerControl : MonoBehaviour {

    public Vector2 movement;

    private IsSpawnLoc bulletSpawnLoc;
    public KeyCode fireButton;

	// Use this for initialization
	void Start () {

        IsSpawnLoc s1 = this.gameObject.GetComponentInChildren<IsSpawnLoc>();

        if (s1 != null) {
            bulletSpawnLoc = s1;
        }
    }

    private void HeroMovementUpdate() {

        movement.x = Input.GetAxis("Horizontal");
        movement.y = Input.GetAxis("Vertical");
        
        this.transform.Translate(movement.y * Vector3.forward);
        this.transform.Translate(movement.x * Vector3.right);
        //this.transform.Rotate(Vector3.up /*y*/, movement.x);
    }

    private void BulletSpawnUpdate() {

        if (Input.GetKeyDown(fireButton) == true) {
            
            if (bulletSpawnLoc != null) {

                bulletSpawnLoc.SpawnObject();
            }
        }
    }

    // Update is called once per frame
    void Update () {

        HeroMovementUpdate();
        BulletSpawnUpdate();
	}
}
