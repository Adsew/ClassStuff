using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DisplayMgr : MonoBehaviour {

    public static DisplayMgr This;

	// Use this for initialization
	void Start () {
		
        if (This == null) {

            This = this;
        }
	}

    public void UpdateText(int num) {

        Text txt = this.gameObject.GetComponent<Text>();

        if (txt != null) {

            txt.text = "" + num;
        }
        else {

            Debug.Log("DisplayMgr: Can't update text component, does not exist.");
        }
    }

    // Update is called once per frame
    void Update () {
		
	}
}
