using System.Collections;
using System.Collections.Generic;
using BehaviourMachine;
using UnityEngine;

[NodeInfo(category = "Miner Bob/Conditions")]
public class IsRichCondition : MinerBobBaseCondition {

    public override Status Update() {

        if (bob == null) {

            return Status.Error;
        }

        if (bob.currentGold >= bob.maxNuggets) {

            return Status.Success;
        }

        return Status.Failure;
    }
}
