using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AstroidLogic : MonoBehaviour {

    public Vector3 moveDir;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {

        if (transform.position.x >= 9.0f || transform.position.x <= -9.0f) {

            moveDir.x *= -1.0f;
        }
        if (transform.position.y >= 6.0f || transform.position.y <= -3.0f) {

            moveDir.y *= -1.0f;
        }

        transform.position += moveDir;
	}
}
