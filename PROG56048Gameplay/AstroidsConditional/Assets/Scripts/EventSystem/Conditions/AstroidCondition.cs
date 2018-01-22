using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AstroidCondition : Condition {
    
    public bool hit = false;

    override public bool condition() {

        return hit;
    }
}
