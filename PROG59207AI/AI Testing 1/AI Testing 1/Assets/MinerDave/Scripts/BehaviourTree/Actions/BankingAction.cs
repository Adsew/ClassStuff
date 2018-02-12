using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

[NodeInfo(category = "Miner Bob/Actions")]
public class BankingAction : MinerBobBAction {

    public override Status Update() {

        bob.deposit(bob.currentGold);

        return Status.Success;
    }
}
