using System.Collections;
using System.Collections.Generic;
using BehaviourMachine;
using UnityEngine;

[NodeInfo(category = "Miner Bob/Actions")]
public class DrinkingAction : MinerBobBAction {

    public float pricePerDrink = 1.0f;
    public float thirstQuenchedPerDrink = 10.0f;
    public float yearsSpent = 0.1f;

    public override Status Update() {
        
        if (bob.currentGold >= pricePerDrink) {

            bob.drink(thirstQuenchedPerDrink, pricePerDrink);
            bob.age(yearsSpent);

            if (bob.thirstLevel <= 0) {

                return Status.Success;
            }

            return Status.Running;
        }

        return Status.Failure;
    }
}
