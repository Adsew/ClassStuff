using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InstantiateAction : Action {

    public GameObject toInstantiate;

    public override void action() {

        if (toInstantiate != null) {

            Instantiate(toInstantiate, transform.position, transform.rotation);
        }
    }
}
