using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsLadder : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}

    private void OnTriggerEnter(Collider other) {

        PlayerMovement p = other.gameObject.GetComponent<PlayerMovement>();

        if (p != null) {

            p.setLadderAvailable(this.gameObject);
        }
    }

    private void OnTriggerExit(Collider other) {

        PlayerMovement p = other.gameObject.GetComponent<PlayerMovement>();

        if (p != null) {

            p.setLadderAvailable(null);
        }
    }

    // Update is called once per frame
    void Update () {
		
	}
}
