using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsProjectile : MonoBehaviour {

	// Use this for initialization
	void Start () {
        Debug.Log("IM WIDE AWAKE");
        SoundMgr.This.PlayRandomFireSound();
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
