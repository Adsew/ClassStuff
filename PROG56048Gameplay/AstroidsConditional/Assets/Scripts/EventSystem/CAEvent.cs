using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CAEvent : MonoBehaviour {

    public Condition condition;
    public Action action;

    private bool registered = false;

	// Use this for initialization
	void Start () {
		

	}
	
	// Update is called once per frame
	void Update () {
		
        if (!registered) {

            registerSelf();
        }
	}

    private void OnDestroy() {
        
        if (registered) {

            EventSystem.This.removeEvent(this);
        }
    }

    private void registerSelf() {

        EventSystem.This.addEvent(this);

        registered = true;
    }
}
