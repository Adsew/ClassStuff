using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TurnLightOff : BaseState {

    private Light _light = null;

    private float currentTime;

    public float delay;

	public new void onEnter(FSM fsm) {

        _light = GetComponent<Light>();
        currentTime = delay;
    }

    public new void execute(FSM fsm) {

        currentTime -= Time.deltaTime;

        if (currentTime < 0.0f) {

            _light.enabled = false;

            fsm.changeState(null);
        }
    }

    public new void onExit(FSM fsm) {


    }
}
