using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsPlayer : MonoBehaviour {

    // Script communicating with an animator

    private Animator anim;
    private IKController ikCont;
    public GameObject myRHand;

    private GameObject objToPickup;
    public float pickupDepth;

    public float v;
    public float h;

    public GameObject ball;

    public GameObject objInHand;

    public float dribblePosition;
    public float dribbleLastTick;
    public float dribbleLastLastTick;

	// Use this for initialization
	void Start () {

        anim = this.gameObject.GetComponent<Animator>();

        if (ikCont == null) {

            ikCont = this.gameObject.GetComponent<IKController>();
        }
	}

    void HeroMovementUpdate() {

        v = Input.GetAxis("Vertical");
        h = Input.GetAxis("Horizontal");
    }

    void HeroAnimationUpdate() {
        
        // Set movements to controller input etc.
        if (anim != null) {

            // SHOULD USE THIS THROUGH INPUT MANAGER ALLOWS DESIGN TIME MODIFICATION WITHOUT CHANIGNG CODE
            if (Input.GetButtonDown("Jump")) {

                anim.SetTrigger("Jump");
            }

            if (Input.GetKeyDown(KeyCode.T)) {

                anim.SetTrigger("Dance");
            }

            if (Input.GetButtonDown("Fire1")) {

                anim.SetTrigger("LightPunch");
            }
            
            if (Input.GetKeyDown(KeyCode.F)) {

                anim.SetTrigger("Fall");
            }

            if (Input.GetKeyDown(KeyCode.E) && objToPickup != null) {
                
                anim.SetTrigger("Pickup");

                IsPickupable ip = objToPickup.GetComponent<IsPickupable>();

                if (ip.rightHandPoint != null) {

                    ikCont.rightHandObj = ip.rightHandPoint.transform;
                }
            }

            anim.SetFloat("Moving", Mathf.Abs(v) + Mathf.Abs(h));
            anim.SetFloat("WalkSpeed", v);
            anim.SetFloat("TurnSpeed", h);

            dribbleLastLastTick = dribbleLastTick;
            dribbleLastTick = dribblePosition;
            dribblePosition = anim.GetFloat("DribbleCurveData");
        }
    }

    void pickupUpdate() {

        IsPickupable ip = null;

        pickupDepth = anim.GetFloat("PickupCurveData");

        if (objToPickup != null) {
            
            ip = objToPickup.GetComponent<IsPickupable>();

            if (ip != null) {

                ikCont.lookObj = objToPickup.transform;
            }
        }

        if (pickupDepth < 0 && objToPickup != null) {

            objInHand = objToPickup;
            objToPickup = null;

            objInHand.transform.parent = myRHand.transform;

            ikCont.lookObj = null;
        }
    }

    void HeroDribbleUpdate() {

        if (ball != null) {

            ball.transform.position = new Vector3(ball.transform.position.x, dribblePosition * 2.0f, ball.transform.position.z);

            if (dribblePosition > dribbleLastTick && dribbleLastTick < dribbleLastLastTick) {
                
                SoundMgr.This.PlayDribble();
            }
        }
    }

	// Update is called once per frame
	void Update () {

        HeroMovementUpdate();
        HeroAnimationUpdate();
        HeroDribbleUpdate();
        pickupUpdate();
	}

    public void setPickupObject(GameObject obj) {

        Debug.Log("I PLAYED");

        if (objToPickup == null) {

            objToPickup = obj;
        }
    }

    public void removePickupObject(GameObject obj) {

        if (obj == objToPickup) {

            objToPickup = null;
        }
    }
}
