using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

[NodeInfo(category = "Miner Bob/Conditions")]
public class IsTiredCondition : MinerBobBaseCondition {
    
    public override Status Update() {

        if (bob == null) {

            return Status.Error;
        }

        if (bob.tirednessThreshold < bob.fatigueLevel) {

            return Status.Success;
        }

        return Status.Failure;
    }
}
