using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour {

    public static Player This;

    public GameObject pGameObject { get; private set; }
    public PlayerControl pControl { get; private set; }
    public GameObject pCameraGameObject;
    public PlayerCamera pCamera { get; private set; }

    public float sightRange = 100.0f;
    public float sightAngle = 90.0f;

    public int maxHealth = 100;

    public int damage = 5;
    
    private int currentHealth;

    private bool needsToDie = false;
    private float timeTilDeath = 5.0f;
    private float deathTimer = 0.0f;

	// Use this for initialization
	void Start () {
		
        if (This == null) {

            This = this;
        }

        if (this.gameObject != null && pGameObject == null) {

            pGameObject = this.gameObject;
            pControl = pGameObject.GetComponent<PlayerControl>();
        }

        if (pCameraGameObject != null) {

            pCamera = pCameraGameObject.GetComponent<PlayerCamera>();
        }

        currentHealth = maxHealth;
	}
	
    public void LockControls(bool setting) {

        if (pControl != null) {

            pControl.lockPlayerControls = setting;
        }
    }

    public void takeDamage(int damage) {

        currentHealth -= damage;
        
        if (currentHealth <= 0) {

            currentHealth = 0;

            if (needsToDie == false) {

                needsToDie = true;

                OnDeath();
            }
        }

        DisplayMgr.This.UpdatePlayerHealth(currentHealth);
    }

    public void heal(int hp) {

        currentHealth += hp;

        if (currentHealth > maxHealth) {

            currentHealth = maxHealth;
        }
    }

    private void OnDeath() {

        LockControls(true);
        DisplayMgr.This.UpdateMessage("Ouch... You died.");

        // Make players turret pop off for fun
        IsTankBody pTankBodyScript = pGameObject.GetComponentInChildren<IsTankBody>();

        if (pTankBodyScript != null) {

            GameObject pTankBody = pTankBodyScript.gameObject;
            IsTurretHead pTurretScript = pGameObject.GetComponentInChildren<IsTurretHead>();

            if (pTurretScript != null) {

                GameObject pTurret = pTurretScript.gameObject;
                Rigidbody turretRB = pTurret.GetComponent<Rigidbody>();
                HingeJoint joint = pTankBody.GetComponent<HingeJoint>();

                if (joint != null && turretRB != null) {

                    pCamera.SetFocusNothing();

                    Destroy(joint);

                    turretRB.velocity = 20.0f * pTurret.transform.up;
                }
            }
        }
    }

    protected void DetermineDeath() {

        if (needsToDie) {

            deathTimer = deathTimer + Time.deltaTime;

            if (deathTimer > timeTilDeath) {

                
            }
        }
    }

    // Update is called once per frame
    void Update () {
		
	}
}
