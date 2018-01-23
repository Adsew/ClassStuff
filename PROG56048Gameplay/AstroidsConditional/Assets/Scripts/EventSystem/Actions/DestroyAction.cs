using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DestroyAction : Action {
    
    override public void action() {

        Destroy(gameObject);
    }
}
