using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CAEvent : MonoBehaviour {

    public List<Condition> conditions = new List<Condition>();
    public List<Action> actions = new List<Action>();

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

    public bool evaluate() {

        if (conditions.Count > 0) {

            bool evaluation = conditions[0].condition();

            foreach (Condition cond in conditions) {

                evaluation = evaluation & cond.condition();
            }

            return evaluation;
        }

        return false;
    }

    public void act() {

        foreach (Action action in actions) {

            action.action();
        }
    }
}
