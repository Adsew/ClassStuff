using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour {

    private Rigidbody2D rbody = null;
    private Animator anim = null;

    private bool isAttacking = false;

    public string hMoveAxis = "Horizontal";
    public string vMoveAxis = "Vertical";

    public string fireButton = "Fire1";

    public float idleCutOff = 0.1f;
    public float xMove, yMove;

    public float speed = 1.0f;
    
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
        
        // Ensures last direction is maintained for facing idle direction
        if (Input.GetAxis(vMoveAxis) != 0 || Input.GetAxis(hMoveAxis) != 0) {

            yMove = Input.GetAxis(vMoveAxis);
            xMove = Input.GetAxis(hMoveAxis);
        }

        // Only move if your past an idle threshold, allowing maintaining direction without movement
        if (rbody != null) {
            if (xMove > idleCutOff || yMove > idleCutOff
                || xMove < -idleCutOff || yMove < -idleCutOff) {

                rbody.velocity = new Vector2(xMove, yMove) * speed;
            }
            else {

                rbody.velocity = new Vector2(0, 0);
            }
        }
        
        if (anim != null) {

            anim.SetFloat(hMoveAxis, xMove);
            anim.SetFloat(vMoveAxis, yMove);

            if (Input.GetButtonDown(fireButton) && !isAttacking) {

                isAttacking = true;

                anim.SetTrigger(fireButton);
            }
        }
    }
}
