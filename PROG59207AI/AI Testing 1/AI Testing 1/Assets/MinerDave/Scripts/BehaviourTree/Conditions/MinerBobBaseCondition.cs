using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

public abstract class MinerBobBaseCondition : ConditionNode {

    protected MinerBob bob;

    public override void Awake() {

        bob = self.gameObject.GetComponent<MinerBob>();
    }
}
