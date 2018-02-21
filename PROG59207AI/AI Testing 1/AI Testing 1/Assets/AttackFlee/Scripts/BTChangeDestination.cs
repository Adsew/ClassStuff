using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

[NodeInfo(category = "General/Actions/")]
public class BTChangeDestination : ActionNode {

    private int curDestination = 0;

    public GameObject[] destinations = new GameObject[0];

    // Update is called once per frame
    public override Status Update () {

        if (destinations.Length > 0) {

            curDestination = (curDestination + 1) % destinations.Length;

            blackboard.GetGameObjectVar("Destination").Value = destinations[curDestination];
        }
        
        return Status.Success;
	}
}
