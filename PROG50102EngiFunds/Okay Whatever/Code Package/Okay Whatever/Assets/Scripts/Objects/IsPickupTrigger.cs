using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsPickupTrigger : MonoBehaviour {

    public GameObject myPickupObj;
    
    private BoxCollider boxcol;

    private bool disabled = false;

	// Use this for initialization
	void Start () {
		
        if (boxcol == null) {

            boxcol = this.gameObject.GetComponent<BoxCollider>();
        }
	}

    private void OnTriggerEnter(Collider other) {

        PlayerAnimation pAnim = other.GetComponent<PlayerAnimation>();
        
        if (pAnim != null) {
            
            pAnim.setPickupObject(myPickupObj);
        }
    }

    private void OnTriggerExit(Collider other) {

        PlayerAnimation pAnim = other.GetComponent<PlayerAnimation>();

        if (pAnim != null) {

            pAnim.removePickupObject(myPickupObj);
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

    public bool TriggerIsActive() {

        return !disabled;
    }

    public void setPickedUp() {

        disabled = true;

        boxcol.enabled = false;
    }

    public void setDropped() {

        disabled = false;

        boxcol.enabled = true;
    }
}
