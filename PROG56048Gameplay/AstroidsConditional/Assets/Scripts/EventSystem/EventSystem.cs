using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EventSystem : MonoBehaviour {

    public static EventSystem This;

    private List<CAEvent> events = new List<CAEvent>();

	// Use this for initialization
	void Start () {
		
        if (This == null) {

            This = this;
        }
	}
	
	// Update is called once per frame
	void Update () {
        
        foreach (CAEvent e in events) {

            if (e.evaluate()) {

                e.act();
            }
        }
	}

    public void addEvent(CAEvent e) {

        if (e != null) {

            events.Add(e);
        }
    }

    public void removeEvent(CAEvent e) {

        if (e != null) {

            events.Remove(e);
        }
    }
}
