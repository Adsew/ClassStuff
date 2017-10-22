using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour {

    public static Player This;

    public GameObject pGameObject { get; private set; }
    public GameObject pBodyGameObject { get; private set; }
    public GameObject pTurretGameObject { get; private set; }

    public PlayerControl pControl { get; private set; }

    public GameObject pCameraGameObject;
    public PlayerCamera pCamera { get; private set; }

    public float sightRange = 100.0f;
    public float sightAngle = 90.0f;

    public int maxHealth = 100;

    public int damage = 5;

    private AudioSource audSrc;

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

            IsTankBody pTankBodyScript = pGameObject.GetComponentInChildren<IsTankBody>();
            IsTurretHead pTankTurretScript = pGameObject.GetComponentInChildren<IsTurretHead>();

            if (pTankBodyScript != null && pBodyGameObject == null) {

                pBodyGameObject = pTankBodyScript.gameObject;
            }
            if (pTankTurretScript != null && pTurretGameObject == null) {

                pTurretGameObject = pTankTurretScript.gameObject;
            }
        }
        if (pCameraGameObject != null) {

            pCamera = pCameraGameObject.GetComponent<PlayerCamera>();
        }

        if (audSrc == null) {

            audSrc = this.gameObject.AddComponent<AudioSource>();
            audSrc.playOnAwake = false;
        }

        currentHealth = maxHealth;
    }

    public void RespawnPlayer(Vector3 spawnLoc) {

        pGameObject.transform.position = spawnLoc;
        pGameObject.transform.rotation = new Quaternion(0, 0, 0, 0);
        pBodyGameObject.transform.localPosition = new Vector3(0, 0, 0);
        pBodyGameObject.transform.rotation = new Quaternion(0, 0, 0, 0);
        pTurretGameObject.transform.localPosition = new Vector3(0, 0.94f, 0);
        pTurretGameObject.transform.rotation = new Quaternion(0, 0, 0, 0);

        HingeJoint turretFixture = pBodyGameObject.GetComponent<HingeJoint>();

        if (turretFixture != null) {

            turretFixture.connectedBody = pTurretGameObject.GetComponent<Rigidbody>();
        }

        currentHealth = maxHealth;

        deathTimer = 0.0f;
        needsToDie = false;

        DisplayMgr.This.UpdatePlayerHealth(currentHealth);
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

        SoundMgr.This.PlayRandomCollisionSound(audSrc);
    }

    public void heal(int hp) {

        currentHealth += hp;

        if (currentHealth > maxHealth) {

            currentHealth = maxHealth;
        }

        DisplayMgr.This.UpdatePlayerHealth(currentHealth);
    }

    private void OnDeath() {

        LockControls(true);
        pCamera.SetFocusNothing();

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
                    
                    joint.connectedBody = null;

                    turretRB.velocity = 20.0f * pTurret.transform.up;

                    SoundMgr.This.PlayRandomExplosionSound(audSrc);
                }
            }
        }
    }

    protected void DetermineDeath() {

        if (needsToDie) {

            deathTimer = deathTimer + Time.deltaTime;

            if (deathTimer > timeTilDeath && !GameStateMgr.This.gameIsOver) {

                GameStateMgr.This.EndGame();
            }
        }
    }

    // Update is called once per frame
    void Update () {

        DetermineDeath();
	}
}
