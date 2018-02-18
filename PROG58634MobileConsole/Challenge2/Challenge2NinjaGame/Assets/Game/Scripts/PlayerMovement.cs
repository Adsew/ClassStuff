using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour {

    private Transform trans = null;
    private Rigidbody2D rbody = null;
    private Animator anim = null;
    private MObjectSpawner spawner = null;

    private bool isAttacking = false;

    public string hMoveAxis = "Horizontal";
    public string vMoveAxis = "Vertical";

    public string fireButton = "Fire1";

    public float idleCutOff = 0.1f;
    public float xMove, yMove;

    public float speed = 1.0f;
    
    public void setAttackingFinished() {

        isAttacking = false;
    }

	// Use this for initialization
	void Start () {

        if (trans == null) {

            trans = transform;
        }
        if (rbody == null) {

            rbody = GetComponent<Rigidbody2D>();
        }
        if (anim == null) {

            anim = GetComponent<Animator>();
        }
        if (spawner == null) {

            spawner = GetComponent<MObjectSpawner>();
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

        // Step is required to stop blend tree from firing all currently blended animation events
        if (spawner != null) {

            float tempH = Mathf.Abs(xMove);
            float tempV = Mathf.Abs(yMove);

            // Tell spawner which direction has highest magnitude,
            // thus player is facing this direction
            if (tempV >= tempH) {

                if (yMove > 0) {

                    spawner.facingDir = 0;
                }
                else {

                    spawner.facingDir = 1;
                }
            }
            else {

                if (xMove > 0) {

                    spawner.facingDir = 2;
                }
                else {

                    spawner.facingDir = 3;
                }
            }
        }
    }
}
