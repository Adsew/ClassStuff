using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

[NodeInfo(category = "Miner Bob/Conditions")]
public class HasGoldCondition : MinerBobBaseCondition {

    public float requiredGold;

    public override Status Update() {

        if (bob == null) {

            return Status.Error;
        }

        if (bob.currentGold >= requiredGold) {

            return Status.Success;
        }

        return Status.Failure;
    }
}
