using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

[NodeInfo(category = "Miner Bob/Conditions")]
public class IsOfAgeCondition : MinerBobBaseCondition {

    public enum Mode {

        LessEquals,
        GreaterEquals,
    }

    public Mode mode = Mode.GreaterEquals;
    public float ageRequired;

    public override Status Update() {

        if (bob == null) {

            return Status.Error;
        }

        if (mode == Mode.GreaterEquals && bob.currentAge >= ageRequired) {

            return Status.Success;
        }

        if (mode == Mode.LessEquals && bob.currentAge <= ageRequired) {

            return Status.Success;
        }

        return Status.Failure;
    }
}
