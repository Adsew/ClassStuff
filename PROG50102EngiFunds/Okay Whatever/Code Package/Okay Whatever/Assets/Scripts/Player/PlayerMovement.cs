using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    private PlayerAnimation pAnimation;
    private Rigidbody myRigidbody;
    private GameObject model;

    public float hMove = 0;
    public float vMove = 0;

    [Range(0.001f, 0.1f)]
    public float speed = 0.005f;
    public float maxSpeed = 0.1f;

    public float maxClimbSpeed = 0.01f;

    public float jumpHeight = 2.0f;

    private bool jump = false;
    private bool awaitingJump = false;
    private bool attack = false;
    private bool pickup = false;
    public bool climbing = false;
    private bool climbLadderTop = false;

    public GameObject ladder = null;
    public bool ladderUpAvailable = true;
    public bool ladderDownAvailable = true;

    private bool lockedControls = false;

    [SerializeField]
    private AudioDatabase jumpAudioDatabase;


    // Use this for initialization
    void Start()
    {

        jumpAudioDatabase.SetAudioSource(GetComponent<AudioSource>());

        if (pAnimation == null)
        {

            pAnimation = this.gameObject.GetComponent<PlayerAnimation>();
        }

        myRigidbody = this.gameObject.GetComponent<Rigidbody>();

        if (myRigidbody == null)
        {

            myRigidbody = this.gameObject.AddComponent<Rigidbody>();
        }

        if (model == null)
        {

            IKController tempIK = this.gameObject.GetComponentInChildren<IKController>();

            if (tempIK != null)
            {

                model = tempIK.gameObject;
            }
            else
            {

                Debug.Log("Player Error: Unable to find player model");
            }
        }

        // Set default direction
        Transform currentTrans = this.gameObject.transform;
        Vector3 currentRotation = currentTrans.eulerAngles;

        currentRotation.x = 0;
        currentRotation.y = 90;
        currentRotation.z = 0;

        currentTrans.localEulerAngles = currentRotation;
    }

    // Get all the input and sort out what needs to be done to the player
    private void PlayerInputUpdate()
    {
        if (!lockedControls)
        {

            float h = Input.GetAxis("Horizontal");
            float v = Input.GetAxis("Vertical");

            // Accelerate in selected direction
            if (h < 0.0f)
            {

                hMove = hMove - speed;

                if (hMove < -maxSpeed)
                {

                    hMove = -maxSpeed;
                }
            }
            else if (h > 0.0f)
            {

                hMove = hMove + speed;

                if (hMove > maxSpeed)
                {

                    hMove = maxSpeed;
                }
            }
            // Not moveing, slow down
            else
            {

                float oldMovement = hMove;

                if (hMove > 0.0f)
                {

                    hMove = hMove - speed;
                }
                else if (hMove < 0.0f)
                {

                    hMove = hMove + speed;
                }

                // If sign changed, crossed 0, means slow to a stop
                if ((hMove * oldMovement) < 0.0f)
                {

                    hMove = 0.0f;
                }
            }

            if (!awaitingJump)
            {
                if (v != 0 && ladder != null
                && (v > 0 && ladderUpAvailable || v < 0 && ladderDownAvailable)
                && ((pAnimation.checkCurrentState("Idle") || pAnimation.checkCurrentState("Motion")) || climbing)
                )
                {

                    climbing = true;

                    vMove = v * maxClimbSpeed;
                }
                else if (climbing && vMove > 0 && !ladderUpAvailable)
                {

                    climbLadderTop = true;
                    climbing = false;

                    vMove = 0;
                }
                else
                {

                    climbing = false;

                    if (Input.GetButtonDown("Jump") && (pAnimation.checkCurrentState("Idle") || pAnimation.checkCurrentState("Motion")))
                    {

                        jump = true;
                    }
                    else if (Input.GetButtonDown("Fire1") && (pAnimation.checkCurrentState("Idle") || pAnimation.checkCurrentState("Motion")))
                    {

                        attack = true;
                    }
                    else if (pAnimation != null && pAnimation.pickupableInRange())
                    {

                        pickup = true;
                    }
                }
            }
        }
    }

    // Tell the animator to perform the animation required by the input
    private void PlayerAnimationUpdate()
    {

        if (pAnimation != null)
        {

            if (jump)
            {

                pAnimation.setJumping();

                awaitingJump = true;
            }
            else if (attack)
            {

                pAnimation.setAttack();
            }
            else if (pickup)
            {

                pAnimation.setPickup();
            }
            else if (climbing)
            {

                pAnimation.setClimbing(true);
                pAnimation.setClimbSpeed(vMove / maxClimbSpeed);
            }
            else if (climbLadderTop)
            {

                pAnimation.setClimbTop(true);
                pAnimation.setClimbSpeed(vMove / maxClimbSpeed);
            }
            else
            {

                pAnimation.setMovement(vMove, hMove / maxSpeed, myRigidbody.velocity.y);
                pAnimation.setClimbing(false);
            }
        }
    }

    // Move the player accordingly
    private void PlayerMovementUpdate()
    {

        Transform currentTrans = this.gameObject.transform;

        // Fix player to z = 0;
        Vector3 p = currentTrans.position;
        p.z = 0;
        currentTrans.position = p;

        if (awaitingJump && (pAnimation.checkCurrentState("RunJump") || pAnimation.checkCurrentState("JumpIdleLeap")))
        {

            if (myRigidbody != null)
            {

                myRigidbody.velocity = new Vector3(hMove, jumpHeight, 0.0f);
                jumpAudioDatabase.PlayRandom();
            }

            awaitingJump = false;
        }
        else if (attack)
        {
        }
        else if (climbing)
        {
            Vector3 currentRotation = currentTrans.eulerAngles;

            currentRotation.x = 0;
            currentRotation.y = 0;
            currentRotation.z = 0;

            currentTrans.localEulerAngles = currentRotation;

            myRigidbody.useGravity = false;
            myRigidbody.velocity = new Vector3(0, 0, 0);

            model.transform.localPosition = new Vector3(0, 0, 0);

            currentTrans.Translate(vMove * Vector3.up);
        }
        else if (climbLadderTop)
        {

            Vector3 currentRotation = currentTrans.eulerAngles;

            currentRotation.x = 0;
            currentRotation.y = 0;
            currentRotation.z = 0;

            currentTrans.localEulerAngles = currentRotation;

            myRigidbody.useGravity = false;

            // End the climbing animation
            if (pAnimation.checkCurrentState("Stand Up"))
            {

                climbLadderTop = false;
                pAnimation.setClimbing(false);

                if (ladder != null)
                {

                    IsLadderEnd[] ends = ladder.GetComponentsInChildren<IsLadderEnd>();

                    if (ends.Length == 2)
                    {

                        IsLadderEnd top;

                        if (ends[0].spot == IsLadderEnd.Position.Top)
                        {

                            top = ends[0];
                        }
                        else
                        {

                            top = ends[1];
                        }

                        currentTrans.position = top.gameObject.transform.position;
                        pAnimation.setClimbTop(false);
                    }
                }
            }
        }
        else
        {

            Vector3 currentRotation = currentTrans.eulerAngles;

            // Rotate in direction of walking
            if (hMove < 0.0f)
            {

                currentRotation.x = 0;
                currentRotation.y = 270;
                currentRotation.z = 0;

                currentTrans.localEulerAngles = currentRotation;
            }
            else if (hMove > 0.0f)
            {

                currentRotation.x = 0;
                currentRotation.y = 90;
                currentRotation.z = 0;

                currentTrans.localEulerAngles = currentRotation;
            }

            currentTrans.Translate(Mathf.Abs(hMove) * Vector3.forward);
        }

        if (!climbing && !climbLadderTop)
        {

            myRigidbody.useGravity = true;
        }

        jump = false;
        attack = false;
        pickup = false;
    }

    // Update is called once per frame
    void Update()
    {

        PlayerInputUpdate();
        PlayerAnimationUpdate();
        PlayerMovementUpdate();
    }

    public void setLadderAvailable(GameObject l)
    {

        ladder = l;
    }

    public void setLadderUpAvailable(bool a)
    {

        ladderUpAvailable = a;
    }

    public void setLadderDownAvailable(bool a)
    {

        ladderDownAvailable = a;
    }

    public void setMovementLock(bool locked)
    {

        lockedControls = locked;

        vMove = 0;
        hMove = 0;

        jump = false;
        awaitingJump = false;
        attack = false;
        pickup = false;
        climbing = false;
        climbLadderTop = false;
    }
}
