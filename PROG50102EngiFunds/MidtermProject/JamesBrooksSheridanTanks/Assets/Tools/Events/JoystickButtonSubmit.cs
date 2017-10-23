using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class JoystickButtonSubmit : MonoBehaviour {
    
    // This script will simply take a button component it is
    // placed with and allow the "Submit" input mapping to
    // trigger it.
    Button thisButton = null;

	// Use this for initialization
	void Start () {
		
        if (thisButton == null) {

            thisButton = this.gameObject.GetComponent<Button>();
        }
	}
	
    void PoleSubmitPressed() {

        if (thisButton != null) {

            if (Input.GetButton("Submit")) {

                thisButton.onClick.Invoke();
            }
        }
    }

	// Update is called once per frame
	void Update () {

        PoleSubmitPressed();
	}
}
