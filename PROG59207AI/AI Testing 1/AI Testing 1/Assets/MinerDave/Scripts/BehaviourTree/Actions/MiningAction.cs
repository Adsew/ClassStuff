using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

[NodeInfo(category = "Miner Bob/Actions")]
public class MiningAction : MinerBobBAction {

    public float thirstIncrease = 5.0f;
    public float goldIncrease = 5.0f;
    public float fatigueIncrease = 10.0f;
    public float yearsSpent = 1.0f;

    public override Status Update() {

        bob.mine(goldIncrease, fatigueIncrease, thirstIncrease);
        bob.age(yearsSpent);

        return Status.Success;
    }
}
