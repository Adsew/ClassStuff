using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ButtonCondition : Condition {

    public KeyCode key;

    public bool hold = true;

    public override bool condition() {

        if (hold) {

            if (Input.GetKey(key)) {

                return true;
            }
        }
        else {

            if (Input.GetKeyDown(key)) {

                return true;
            }
        }

        return false;
    }
}
