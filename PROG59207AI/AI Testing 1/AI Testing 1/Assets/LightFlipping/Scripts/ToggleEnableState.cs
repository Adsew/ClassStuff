using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ToggleEnableState :  BaseState {
    
    private float currentTime;

    public BaseState nextState;

    public Behaviour component;

    public string comment;

    public float delay;

    public new void onEnter(FSM fsm) {
        
        currentTime = delay;
    }

    public new void execute(FSM fsm) {

        currentTime -= Time.deltaTime;

        if (currentTime < 0.0f) {

            component.enabled = !component.enabled;

            fsm.changeState(nextState);
        }
    }

    public new void onExit(FSM fsm) {


    }
}
