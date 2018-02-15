using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

public class BStartState : StateBehaviour {

    private float timer = 0.0f;

    public float timeTilStart;

	void OnEnable() {

        timer = 0.0f;
    }

    void Update() {

        timer += Time.deltaTime;

        if (timer >= timeTilStart) {

            SendEvent("FINISHED");
        }
    }
}
