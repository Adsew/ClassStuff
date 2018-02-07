using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ProfWalkAnimMove : MonoBehaviour {

    private Animator anim;

	// Use this for initialization
	void Start () {

        anim = GetComponent<Animator>();
	}

    // Update is called once per frame
    void Update() {

        if (anim != null) {

            if (Input.GetKey("w")) {

                anim.SetBool("GoUp", true);
            }
            else {

                anim.SetBool("GoUp", false);
            }

            if (Input.GetKey("a")) {

                anim.SetBool("GoLeft", true);
            }
            else {

                anim.SetBool("GoLeft", false);
            }

            if (Input.GetKey("d")) {

                anim.SetBool("GoRight", true);
            }
            else {

                anim.SetBool("GoRight", false);
            }

            if (Input.GetKey("s")) {

                anim.SetBool("GoDown", true);
            }
            else {

                anim.SetBool("GoDown", false);
            }
        }
        else {

            Debug.Log("Cant find animator");
        }
    }
}
