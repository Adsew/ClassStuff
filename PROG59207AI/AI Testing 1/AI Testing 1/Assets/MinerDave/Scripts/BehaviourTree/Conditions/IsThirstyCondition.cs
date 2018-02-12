using System.Collections;
using System.Collections.Generic;
using BehaviourMachine;
using UnityEngine;

[NodeInfo(category = "Miner Bob/Conditions")]
public class IsThirstyCondition : MinerBobBaseCondition {

    public override Status Update() {

        if (bob == null) {

            return Status.Error;
        }

        if (bob.thirstLevel >= bob.thirstThreshold) {

            return Status.Success;
        }

        return Status.Failure;
    }
}
