using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AEquipSlot : MonoBehaviour {

    public enum SlotType {

        Head,
        Foot,
        Hand
    }

    public SlotType slotType;

    private Animator myAnimator = null;
    private RuntimeAnimatorController originalAnimation = null;

    private AEquipable inSlot;

    private void Start() {

        myAnimator = this.GetComponentInParent<Animator>();

        if (myAnimator != null) {

            originalAnimation = myAnimator.runtimeAnimatorController;
        }
    }

    public bool equip(AEquipable item, RuntimeAnimatorController controller) {

        if (inSlot == null && item.slotType == slotType) {

            inSlot = item;

            inSlot.transform.parent = transform;

            inSlot.transform.localPosition = Vector3.zero;

            if (myAnimator != null && inSlot.controller != null) {

                myAnimator.runtimeAnimatorController = inSlot.controller;
            }

            return true;
        }

        return false;
    }

    public bool unequip() {

        if (inSlot != null) {

            inSlot.drop();
            inSlot = null;

            myAnimator.runtimeAnimatorController = originalAnimation;

            return true;
        }

        return false;
    }
}
