using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AEquipable : MonoBehaviour {

    private bool equiped = false;

    public AnimatorOverrideController controller;

    public AEquipSlot.SlotType slotType;

    public void equip() {

        if (!equiped) {

            ACollidable collider = GetComponent<ACollidable>();

            if (collider != null) {

                List<Component> matches = collider.getObjectsOfType(typeof(AEquipSlot));

                foreach (Component es in matches) {

                    AEquipSlot slot = (AEquipSlot)es;

                    if (slot.slotType == slotType) {

                        if (slot.equip(this, controller)) {

                            equiped = true;

                            break;
                        }
                    }
                }
            }
        }
    }

    public void drop() {

        equiped = false;
    }
}
