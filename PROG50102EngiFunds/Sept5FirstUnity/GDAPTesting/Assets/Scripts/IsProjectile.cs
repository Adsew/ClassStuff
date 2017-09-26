using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsProjectile : MonoBehaviour {

	// Use this for initialization
	void Start () {
        
        SoundMgr.This.PlayRandomFireSound();
	}

    private void OnCollisionEnter(Collision collision) {
        

    }

    // Update is called once per frame
    void Update () {
		
	}
}
