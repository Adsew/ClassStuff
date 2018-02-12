using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

[NodeInfo(category = "Miner Bob/Actions")]
public class SleepingAction : MinerBobBAction {

    public float fatigueRemoved = -10.0f;
    public float yearsSpent = 0.1f;

    public override Status Update() {

        bob.sleep(fatigueRemoved);
        bob.age(yearsSpent);
        
        if (bob.fatigueLevel <= 0) {

            return Status.Success;
        }

        return Status.Running;
    }
}
