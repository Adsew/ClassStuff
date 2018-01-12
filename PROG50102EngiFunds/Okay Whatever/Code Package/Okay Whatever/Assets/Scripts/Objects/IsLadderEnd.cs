using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsLadderEnd : MonoBehaviour {

    public enum Position {

        Top,
        Bottom
    };

    public Position spot = Position.Bottom;

    // Use this for initialization
    void Start () {
		
	}

    private void OnTriggerEnter(Collider other) {

        PlayerMovement pm = other.gameObject.GetComponent<PlayerMovement>();

        if (pm != null) {

            if (spot == Position.Bottom) {

                pm.setLadderDownAvailable(false);
            }
            if (spot == Position.Top) {

                pm.setLadderUpAvailable(false);
            }
        }
    }

    private void OnTriggerExit(Collider other) {

        PlayerMovement pm = other.gameObject.GetComponent<PlayerMovement>();

        if (pm != null) {

            if (spot == Position.Bottom) {

                pm.setLadderDownAvailable(true);
            }
            if (spot == Position.Top) {

                pm.setLadderUpAvailable(true);
            }
        }
    }

    // Update is called once per frame
    void Update () {
		
	}
}
