using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

public abstract class MinerBobBAction : ActionNode {

    protected MinerBob bob;

    public override void Awake() {

        bob = self.gameObject.GetComponent<MinerBob>();
    }
}
