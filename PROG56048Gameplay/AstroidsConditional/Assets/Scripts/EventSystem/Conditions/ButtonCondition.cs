using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ButtonCondition : Condition {

    public KeyCode key;

    public override bool condition() {

        if (Input.GetKey(key)) {

            return true;
        }

        return false;
    }
}
