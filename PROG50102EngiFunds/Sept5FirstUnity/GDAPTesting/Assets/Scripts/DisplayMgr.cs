using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DisplayMgr : MonoBehaviour {


    public static DisplayMgr This;

    public void UpdateText(int num)
    {
        Text txt = this.gameObject.GetComponent<Text>();
        
        txt.text = "Score = " + num;
    }

	// Use this for initialization
	void Start () {
		
        if (This == null)
        {
            This = this;
        }
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
