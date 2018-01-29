using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FSM : MonoBehaviour {
    
    [SerializeField]
    private BaseState currentState = null;

	// Use this for initialization
	void Start () {

        if (currentState != null) {

            currentState.onEnter(this);
        }
    }
	
	// Update is called once per frame
	void Update () {
		
        if (currentState != null) {

            currentState.execute(this);
        }
	}

    public void changeState(BaseState newState) {

        if (newState != null) {

            if (currentState != null) {

                currentState.onExit(this);
            }

            currentState = newState;

            currentState.onEnter(this);
        }
        else {

            Debug.LogError("D");
        }
    }
}
