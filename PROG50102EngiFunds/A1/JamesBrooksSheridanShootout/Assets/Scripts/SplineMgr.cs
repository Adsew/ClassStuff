using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SplineMgr : MonoBehaviour {

    // Allow targets access to spline information
    public GameObject splineLeft;
    public GameObject splineRight;

    public static SplineMgr This;

	// Use this for initialization
	void Start () {

        This = this;
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
