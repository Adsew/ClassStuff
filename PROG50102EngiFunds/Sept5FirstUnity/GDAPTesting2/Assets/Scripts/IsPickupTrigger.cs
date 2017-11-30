using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsPickupTrigger : MonoBehaviour {

    public GameObject myPickupObj;
    public GameObject playerObj;

    private IsPlayer player;

	// Use this for initialization
	void Start () {
		
        if (playerObj != null) {

            player = playerObj.GetComponent<IsPlayer>();
        }
	}

    private void OnTriggerEnter(Collider other) {
        
        if (player != null && other.gameObject.transform == playerObj.transform) {

            player.setPickupObject(myPickupObj);
        }
    }

    private void OnTriggerExit(Collider other) {
        
        if (player != null && other.gameObject.transform == playerObj.transform) {

            player.removePickupObject(myPickupObj);
        }
    }
    
    void PositionUpdate() {

        if (myPickupObj != null) {

            transform.position = myPickupObj.transform.position;
            transform.rotation = myPickupObj.transform.rotation;
        }
    }

    // Update is called once per frame
    void Update () {

        PositionUpdate();
	}
}
