using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

[NodeInfo(category = "Miner Bob/Actions")]
public class DieAction : MinerBobBAction {

    public override Status Update() {

        if (bob == null) {

            return Status.Error;
        }

        GameObject.Destroy(bob.gameObject);

        return Status.Success;
    }
}
