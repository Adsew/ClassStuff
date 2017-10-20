using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class IsHealthbar : MonoBehaviour {

    private Transform canvasTrans = null;

    private Image bar = null;

	// Use this for initialization
	void Start () {
		
        if (bar == null) {

            bar = this.gameObject.GetComponent<Image>();
        }
        if (bar != null && canvasTrans == null) {

            canvasTrans = this.gameObject.transform.parent; // Parent must be canvas if we are a UI element
        }
	}
	
    // Keep HealthBar facing the player
    private void RotationUpdate() {

        canvasTrans.forward = (Player.This.pGameObject.transform.position - canvasTrans.position).normalized;
    }

    // Uses decimal percent from 0 to 1
    public void SetHealthPercent(float percent) {
        
        if (percent >= 0.0f && percent <= 1.0f) {

            bar.fillAmount = percent;
        }
    }

	// Update is called once per frame
	void Update () {

        RotationUpdate();
	}
}
