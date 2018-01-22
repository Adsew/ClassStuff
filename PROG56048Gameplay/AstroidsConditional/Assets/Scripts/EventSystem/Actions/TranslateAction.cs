using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TranslateAction : Action {

    public float speed;

    override public void action() {

        transform.position += transform.up * speed;
    }
}
