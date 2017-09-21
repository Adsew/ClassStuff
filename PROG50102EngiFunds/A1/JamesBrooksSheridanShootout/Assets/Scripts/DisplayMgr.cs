using System.Collections;
using System.Collections.Generic;
using UnityEngine;

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

        txt.text = "Score = " + num;
    }

    // Update is called once per frame
    void Update () {
		
	}
}
