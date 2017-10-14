using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerControl : MonoBehaviour {
    
    private IsSpawnLocCannon bulletSpawnLoc;
    private GameObject body;
    private GameObject turret;
    private GameObject cannon;

    private const float deadZone = 0.1f;

    private float curSpeed;   // 
    
    [Range(0.1f, 5.0f)]
    public float timeBetweenShots = 1.0f;
    private float timeSinceShot;
    
    [Range(0.001f,0.01f)]
    public float acceleration = 0.003f;

    [Range(0.1f, 1.0f)]
    public float maxSpeed = 0.5f;

    [Range(0.01f, 0.1f)]
    public float bodyRotationSpeed = 0.05f;

    // Controls Visibility
    public float xMove;
    public float yMove;
    public float xLook;
    public float yLook;
    public float fire1;

	// Use this for initialization
	void Start () {

        IsSpawnLocCannon tempSpawn = this.gameObject.GetComponentInChildren<IsSpawnLocCannon>();
        IsTankBody tempBody = this.gameObject.GetComponentInChildren<IsTankBody>();
        IsTurretHead tempHead = this.gameObject.GetComponentInChildren<IsTurretHead>();
        IsCannon tempCannon = this.gameObject.GetComponentInChildren<IsCannon>();

        if (tempSpawn != null) {

            bulletSpawnLoc = tempSpawn;
        }

        if (tempBody != null) {
            if (tempBody.gameObject != null) {

                body = tempBody.gameObject;
            }
        }
        
        if (tempHead != null) {
            if (tempHead.gameObject != null) {

                turret = tempHead.gameObject;
            }
        }

        if (tempCannon != null) {
            if (tempCannon.gameObject != null) {

                cannon = tempCannon.gameObject;
            }
        }
        
        curSpeed = 0.0f;
        timeSinceShot = 0.0f;
    }
    
    // Hero translation movement
    private void HeroMovementUpdate() {
        
        Vector3 finalTranslation;
        xMove = Input.GetAxis("Move Horizontal");
        yMove = Input.GetAxis("Move Vertical");

        Quaternion turretRotation = turret.transform.rotation;
        Vector3 crossResult = new Vector3();

        // Rotate towards movement direction based on turret position
        if (xMove > deadZone) {

            crossResult = Vector3.Cross(turret.transform.right, body.transform.forward);
        }
        else if (xMove < -deadZone) {

            crossResult = Vector3.Cross(-turret.transform.right, body.transform.forward);
        }

        if (yMove > deadZone) {

            crossResult = Vector3.Cross(turret.transform.forward, body.transform.forward);
        }
        else if (yMove < -deadZone) {

            crossResult = Vector3.Cross(-turret.transform.forward, body.transform.forward);
        }

        if (crossResult.y < -0.02f) {
            //turn left
            body.transform.Rotate(body.transform.up, 1);
        }
        else if (crossResult.y > 0.02f) {
            // turn right
            body.transform.Rotate(body.transform.up, -1);
        }

        // Based on speedup/slowdown movement rather than direct movement

        // Forward-back movement
        // Only accelerate if not turning hard turning
        if (Mathf.Abs(yMove) > deadZone
            || Mathf.Abs(xMove) > deadZone) {
            if (curSpeed < maxSpeed) {
                if (crossResult.y < 0.7f && crossResult.y > -0.7f) {

                    curSpeed = curSpeed + acceleration;
                }
            }
        }
        
        // Not moveing, slow down
        else {

            float oldMovement = curSpeed;

            if (curSpeed > 0.0f) {

                curSpeed = curSpeed - acceleration;
            }
            else if (curSpeed < 0.0f) {

                curSpeed = curSpeed + acceleration;
            }

            // If sign changed, trying to move opposite direction, means slow down
            if ((curSpeed * oldMovement) < 0.0f) {

                curSpeed = 0.0f;
            }
        }
        
        finalTranslation = curSpeed * body.transform.forward;
        this.gameObject.transform.Translate(finalTranslation);
    }

    // Hero aiming rotation
    private void HeroCannonRotationUpdate() {

        Vector2 rotate;
        Vector2 currRotation;

        xLook = Input.GetAxis("Look Horizontal");
        yLook = Input.GetAxis("Look Vertical");

        rotate.x = xLook;
        rotate.y = yLook;

        currRotation.x = cannon.transform.localRotation.x;
        currRotation.y = cannon.transform.localRotation.y;

        if (turret != null && cannon != null) {

            // Turret Left-Right rotation
            if (rotate.x > 0) {

                turret.transform.Rotate(Vector3.up, rotate.x);
            }
            else if (rotate.x < 0) {

                turret.transform.Rotate(Vector3.up, rotate.x);
            }

            // Cannon Up-Down rotation
            // Keep cannon within certain bounds of rotation
            if (-rotate.y > 0 && currRotation.x < 0.0f) {

                cannon.transform.Rotate(Vector3.right, -rotate.y);
            }
            else if (-rotate.y < 0 && currRotation.x > -0.35f) {

                cannon.transform.Rotate(Vector3.right, -rotate.y);
            }
        }
    }

    // Fire projectile
    private void BulletSpawnUpdate() {

        fire1 = Input.GetAxis("Fire1");
        timeSinceShot += Time.deltaTime;

        if (fire1 > 0.1f && timeSinceShot >= timeBetweenShots) {

            timeSinceShot = 0.0f;

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
