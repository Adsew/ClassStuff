using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerControl : MonoBehaviour {

    private GameObject player;
    private IsSpawnCannonBallLoc bulletSpawnLoc;
    private GameObject cannon;

    private float lrMovement;

    [Range(0.01f,0.1f)]
    public float moveSpeed = 0.03f;

    public KeyCode fireButton;

    public KeyCode moveLeft;
    public KeyCode moveRight;

    public KeyCode rotateLeft;
    public KeyCode rotateRight;
    public KeyCode rotateUp;
    public KeyCode rotateDown;

	// Use this for initialization
	void Start () {
        
        IsSpawnCannonBallLoc tempSpawn = this.gameObject.GetComponentInChildren<IsSpawnCannonBallLoc>();
        IsCannon tempCannon = this.gameObject.GetComponentInChildren<IsCannon>();
        
        if (tempSpawn != null) {

            bulletSpawnLoc = tempSpawn;
        }
        if (tempCannon != null) {
            if (tempCannon.gameObject != null) {

                cannon = tempCannon.gameObject;
            }
        }

        player = this.gameObject;
        lrMovement = 0.0f;
    }

    // Hero aiming movement
    private void HeroCannonRotationUpdate() {

        Vector2 rotate;
        Vector2 currRotation;

        rotate.x = Input.GetAxis("Horizontal");
        rotate.y = Input.GetAxis("Vertical");

        currRotation.x = cannon.transform.rotation.x;
        currRotation.y = cannon.transform.rotation.y;
        
        // Keep cannon within certain bounds of rotation
        if ( rotate.x > 0 && currRotation.y < 0.25f) {

            cannon.transform.Rotate(Vector3.up, rotate.x);
        }
        else if (rotate.x < 0 && currRotation.y > -0.25f) {

            cannon.transform.Rotate(Vector3.up, rotate.x);
        }

        if (-rotate.y > 0 && currRotation.x < 0.0f) {

            cannon.transform.Rotate(Vector3.right, -rotate.y);
        }
        else if (-rotate.y < 0 && currRotation.x > -0.35f) {

            cannon.transform.Rotate(Vector3.right, -rotate.y);
        }

        // Maintain cannon proper angle when rotating
        cannon.transform.Rotate(Vector3.forward, -(cannon.transform.rotation.z * 180.0f / 3.14f));
    }

    // Hero translation movement
    private void HeroMovementUpdate() {

        // Remove case of both buttons down (no movement should happen)
        if (Input.GetKey(moveLeft) == true && Input.GetKey(moveRight) == true) {


        }
        // Also ensure player does not leave stage area
        else if (Input.GetKey(moveLeft) == true
            && lrMovement > -1.0f
            && player.transform.position.x > -8.0f) {

            lrMovement = lrMovement - moveSpeed;
        }
        else if (Input.GetKey(moveRight) == true
            && lrMovement < 1.0f
            && player.transform.position.x < 12.0f) {

            lrMovement = lrMovement + moveSpeed;
        }
        // Not moveing, slow down
        else {

            float oldMovement = lrMovement;

            if (lrMovement > 0.0f) {

                lrMovement = lrMovement - moveSpeed;
            }
            else if (lrMovement < 0.0f) {

                lrMovement = lrMovement + moveSpeed;
            }

            // If sign changed, crossed 0, means slow to a stop
            if ((lrMovement * oldMovement) < 0.0f) {

                lrMovement = 0.0f;
            }
        }

        this.transform.Translate(lrMovement * Vector3.right);
    }

    // Fire our projectiles
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
        HeroCannonRotationUpdate();
        BulletSpawnUpdate();
	}
}
