using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ControlsMgr : MonoBehaviour {

    public ControlsMgr Instance;

	// Use this for initialization
	void Start () {
		
        if (Instance == null) {

            Instance = this;
        }
	}
	
    void ControlsUpdate() {

        if (Input.GetKeyDown(KeyCode.Tab)) {

            UIMgr.Instance.SetPanelID(2);
        }

        if (Input.GetKeyUp(KeyCode.Tab)) {

            UIMgr.Instance.SetPanelID(3);
        }
    }

	// Update is called once per frame
	void Update () {

        ControlsUpdate();
	}
}
