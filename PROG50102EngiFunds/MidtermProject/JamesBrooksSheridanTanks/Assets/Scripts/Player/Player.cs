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
    public int maxAmmo = 10;
    
    private int currentHealth;
    private int currentAmmo;

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
        currentAmmo = maxAmmo;
	}
	
    public void LockControls(bool setting) {

        if (pControl != null) {

            pControl.lockPlayerControls = setting;
        }
    }

    public void takeDamage(int damage) {

        currentHealth -= damage;

        if (currentHealth < 0) {

            currentHealth = 0;
        }
    }

    public void heal(int hp) {

        currentHealth += hp;

        if (currentHealth > maxHealth) {

            currentHealth = maxHealth;
        }
    }

	// Update is called once per frame
	void Update () {
		
	}
}
