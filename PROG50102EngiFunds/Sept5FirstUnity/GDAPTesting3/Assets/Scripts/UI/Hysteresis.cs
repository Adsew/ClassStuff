using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Hysteresis : MonoBehaviour {

    public GameObject tgtObj;
    public float kh;

    public void setTgt(GameObject obj) {

        tgtObj = obj;
    }

	// Use this for initialization
	void Start () {
		
	}
	
    public void HysteresisUpdate() {

        if (tgtObj) {

            this.transform.position += kh * (tgtObj.transform.position - this.transform.position);
        }
    }

	// Update is called once per frame
	void Update () {

        HysteresisUpdate();
	}
}
