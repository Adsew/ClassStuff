using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StandardMovement : MonoBehaviour {

    // Script communicating with an animator

    private Animator anim;
    
    public float v;
    public float h;

	// Use this for initialization
	void Start () {

        anim = this.gameObject.GetComponent<Animator>();
	}

    void HeroMovementUpdate() {

        v = Input.GetAxis("Vertical");
        h = Input.GetAxis("Horizontal");
    }

    void HeroAnimationUpdate() {
        
        // Set movements to controller input etc.
        if (anim != null) {

            // SHOULD USE THIS THROUGH INPUT MANAGER ALLOWS DESIGN TIME MODIFICATION WITHOUT CHANIGNG CODE
            if (Input.GetButtonDown("Jump")) {

                anim.SetTrigger("Jump");
            }

            if (Input.GetKeyDown(KeyCode.T)) {

                anim.SetTrigger("Dance");
            }

            if (Input.GetButtonDown("Fire1")) {

                anim.SetTrigger("LightPunch");
            }

            anim.SetFloat("Moving", Mathf.Abs(v + h));
            anim.SetFloat("WalkSpeed", v);
            anim.SetFloat("TurnSpeed", h);
        }
    }

	// Update is called once per frame
	void Update () {

        HeroMovementUpdate();
        HeroAnimationUpdate();
	}
}
