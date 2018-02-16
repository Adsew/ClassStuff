using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour {

    private Rigidbody2D rbody = null;
    private Animator anim = null;

    public string hMoveAxis = "Horizontal";
    public string vMoveAxis = "Vertical";

    public string fireButton = "Fire1";

    public float xMove, yMove;

	// Use this for initialization
	void Start () {

        if (rbody == null) {

            rbody = GetComponent<Rigidbody2D>();
        }
        if (anim == null) {

            anim = GetComponent<Animator>();
        }
	}
	
	// Update is called once per frame
	void Update () {

        xMove = Input.GetAxis(hMoveAxis);
        yMove = Input.GetAxis(vMoveAxis);
        
        if (rbody != null) {

            rbody.velocity = new Vector2(xMove, yMove);
        }

        if (anim != null) {

            anim.SetFloat(hMoveAxis, xMove);
            anim.SetFloat(vMoveAxis, yMove);
        }
    }
}
