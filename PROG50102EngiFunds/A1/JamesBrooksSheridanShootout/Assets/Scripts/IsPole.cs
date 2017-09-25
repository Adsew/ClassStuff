using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsPole : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
    void OnJointBreak(float bf) {

        SoundMgr.This.PlayRandomTargetSound();
    }

	// Update is called once per frame
	void Update () {
		
	}
}
