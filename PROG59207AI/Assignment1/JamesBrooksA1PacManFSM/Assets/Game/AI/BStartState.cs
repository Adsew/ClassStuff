using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

public class BStartState : StateBehaviour {

	void OnEnable() {

        SendEvent("FINISHED");
    }
}
