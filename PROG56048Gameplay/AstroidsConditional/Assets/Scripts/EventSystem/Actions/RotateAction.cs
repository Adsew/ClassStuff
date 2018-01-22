using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotateAction : Action {

    public Vector3 rotateDir;

	override public void action() {

        transform.Rotate(rotateDir);
    }
}
