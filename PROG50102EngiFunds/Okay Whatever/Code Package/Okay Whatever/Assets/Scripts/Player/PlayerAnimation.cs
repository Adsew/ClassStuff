using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAnimation : MonoBehaviour {

    // Script communicating with an animator
    
    private Animator anim;

    private IKController ikCont;

    private PlayerMovement pMovement = null;

    private ObjectPositionTracker groundCollidor;

    public RuntimeAnimatorController myAnimPack;
    
    private GameObject myRHand;

    public GameObject objInHand;

    private GameObject objToPickup;
    private GameObject objToPickupHandle;

    private bool currentlyPickingup = false;

    private bool playerIsDead = false;

	// Use this for initialization
	void Start () {
        
        anim = this.gameObject.GetComponentInChildren<Animator>();

        if (anim != null) {

            anim.runtimeAnimatorController = myAnimPack;
        }

        if (ikCont == null) {

            ikCont = this.gameObject.GetComponentInChildren<IKController>();
            ikCont.ikActive = true;
        }

        if (pMovement == null) {

            pMovement = this.gameObject.GetComponent<PlayerMovement>();
        }

        if (groundCollidor == null) {

            groundCollidor = this.gameObject.GetComponentInChildren<ObjectPositionTracker>();
        }

        if (myRHand == null) {

            IsPlayerRHand rh = this.gameObject.GetComponentInChildren<IsPlayerRHand>();

            if (rh != null) {

                myRHand = rh.gameObject;
            }
        }
	}
    
    public bool setMovement(float v, float h, float fallSpeed) {

        if (anim != null && playerIsDead == false) {

            anim.SetFloat("Moving", Mathf.Abs(v) + Mathf.Abs(h));
            anim.SetFloat("WalkSpeed", h);
            anim.SetFloat("FallSpeed", fallSpeed);

            return true;
        }

        return false;
    }

    public bool setClimbSpeed(float s) {

        if (anim != null && playerIsDead == false) {

            anim.SetFloat("ClimbSpeed", s);

            return true;
        }

        return false;
    }

    public bool setJumping() {

        if (anim != null && playerIsDead == false) {

            anim.SetTrigger("Jump");

            return true;
        }

        return false;
    }
    
    public bool setAttack() {

        if (anim != null && objInHand != null && playerIsDead == false) {

            anim.SetTrigger("UseObj");
            anim.SetBool("HasItem", true);

            return true;
        }

        return false;
    }

    public bool setClimbing(bool isClimbing) {

        if (anim != null && playerIsDead == false) {

            anim.SetBool("Climbing", isClimbing);

            return true;
        }

        return false;
    }
    
    public bool setClimbTop(bool climbTop) {

        if (anim != null && playerIsDead == false) {

            anim.SetBool("ClimbTop", climbTop);

            return true;
        }

        return false;
    }

    public bool setDancing() {

        if (anim != null && playerIsDead == false) {

            anim.SetTrigger("Dance");

            return true;
        }

        return false;
    }

    public void setHasWeapon(bool hasWep) {

        if (anim != null && playerIsDead == false) {

            anim.SetBool("HasWeapon", hasWep);
        }
    }

    public bool pickupableInRange() {

        if (objToPickup != null && objInHand == null && !currentlyPickingup) {

            return true;
        }

        return false;
    }

    public bool setPickup() {

        // Set movements to controller input etc.
        if (anim != null && playerIsDead == false) {

            // Pickup object
            if (objToPickup != null && objInHand == null) {
                
                anim.SetTrigger("Pickup");

                currentlyPickingup = true;

                pMovement.setMovementLock(true);

                IsPickupable ip = objToPickup.GetComponent<IsPickupable>();

                if ((objToPickupHandle = ip.getClosestHandle(this.gameObject.transform.position)) != null) {

                    Rigidbody rb;

                    if (rb = ip.gameObject.GetComponent<Rigidbody>()) {

                        Destroy(rb);
                    }

                    ikCont.rightHandObj = objToPickupHandle.transform;
                }

                return true;
            }

            // Drop object
            else if (objInHand != null) {

                IsPickupable ip = objInHand.GetComponent<IsPickupable>();

                if (ip != null) {

                    ip.drop();
                }
                
                objInHand = null;

                ikCont.rightHandObj = null;
                ikCont.leftHandObj = null;

                anim.runtimeAnimatorController = myAnimPack;

                anim.SetBool("HasItem", false);

                return true;
            }
        }

        return false;
    }

    public bool setDying() {

        if (anim != null) {

            anim.SetTrigger("Die");

            playerIsDead = true;

            return true;
        }
        
        return false;
    }

    public bool setReviveFromDeath() {

        if (anim != null && playerIsDead) {

            anim.SetTrigger("Revive");

            playerIsDead = false;

            return true;
        }

        return false;
    }

    public void setPickupObject(GameObject obj) {

        if (objToPickup == null) {

            objToPickup = obj;
        }
    }

    public void removePickupObject(GameObject obj) {

        if (obj == objToPickup) {

            objToPickup = null;
            objToPickupHandle = null;
        }
    }
    
    void pickupUpdate() {

        IsPickupable ip = null;

        float pickupDepth = anim.GetFloat("PickupCurveData");

        if (objToPickup != null) {

            ip = objToPickup.GetComponent<IsPickupable>();

            if (ip != null) {

                ikCont.lookObj = objToPickup.transform;
            }

            if (currentlyPickingup) {

                ikCont.rightHandWeight = 1.0f - pickupDepth;
            }
        }
        else {

            ikCont.lookObj = null;
        }

        if (pickupDepth < 0 && ip != null) {
            
            objInHand = objToPickup;
            
            myRHand.transform.position = objToPickupHandle.transform.position;

            objInHand.transform.parent = myRHand.transform;

            if (ip != null) {

                ip.pickup(this);
            }

            if (ip.animOverride != null) {

                anim.SetBool("HasItem", true);

                anim.runtimeAnimatorController = ip.animOverride;
            }

            ikCont.lookObj = null;
            objToPickup = null;
            objToPickupHandle = null;

            currentlyPickingup = false;

            pMovement.setMovementLock(false);
        }
    }
    
    public bool checkCurrentState(string stateName) {

        return anim.GetCurrentAnimatorStateInfo(0).IsName(stateName);
    }

    // Updates the collider box to ensure we can go down ladders
    private void collisionUpdate() {

        if (!pMovement.ladderUpAvailable && pMovement.climbing) {

            groundCollidor.gameObject.SetActive(false);
        }
        else {

            groundCollidor.gameObject.SetActive(true);
        }
    }

	// Update is called once per frame
	void Update () {

        collisionUpdate();
        pickupUpdate();
	}
}
