using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HeroMovement : MonoBehaviour {


    public Vector2 axis;

	// Use this for initialization
	void Start () {
		
	}

    public void HeroMovementUpdate(){

        axis.x = Input.GetAxis("Horizontal");         //filtered is over a few frames for smoother input, raw is straight.
        axis.y = Input.GetAxis("Vertical");

        // think about framerate as well with this
        this.transform.Translate( axis.y * Vector3.forward );
        this.transform.Rotate( Vector3.up /*y*/, axis.x );
    }

	// Update is called once per frame
	void Update () {

        HeroMovementUpdate();
	}
}
