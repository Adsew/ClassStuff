using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviourMachine;

public abstract class BGhostState : StateBehaviour {

    protected GhostController gControl = null;
    protected Transform myTrans = null;
    protected Animator anim = null;
    protected GameDirector.States state = GameDirector.States.enState_Normal;

    protected void Awake() {

        if (gControl == null) {

            gControl = GetComponent<GhostController>();
        }
        if (myTrans == null) {

            myTrans = transform;
        }
        if (anim == null) {

            anim = GetComponent<Animator>();
        }
    }

    public void GameStateChanged(GameDirector.States _state) {

        state = _state;
    }
}
