using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerStats : MonoBehaviour {

    public static PlayerStats This;

    public GameObject player { get; private set; }

    public int maxHealth;
    public int maxAmmo;
    
    private int currentHealth;
    private int currentAmmo;

	// Use this for initialization
	void Start () {
		
        if (This == null) {

            This = this;
        }

        if (this.gameObject != null) {

            player = this.gameObject;
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
