using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StandardMovement : MonoBehaviour {

    // Script communicating with an animator

    private Animator anim;
    

	// Use this for initialization
	void Start () {

        anim = this.gameObject.GetComponent<Animator>();
	}

    void HeroMovementUpdate() {

        
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

            if (Input.GetButton("Vertical")) {

                anim.SetBool("Walking", true);
            }
            else {

                anim.SetBool("Walking", false);
            }
        }
    }

	// Update is called once per frame
	void Update () {

        HeroMovementUpdate();
        HeroAnimationUpdate();
	}
}
