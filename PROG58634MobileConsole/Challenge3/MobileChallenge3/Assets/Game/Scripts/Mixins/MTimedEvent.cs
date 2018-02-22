using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class MTimedEvent : MonoBehaviour {

    private float timer;

    private bool timing = false;

    public float timeTilEvent = 1.0f;

    public UnityEvent timedEvent;

    public void startTimer() {

        timer = 0;

        timing = true;
    }

	// Update is called once per frame
	void Update () {
		
        if (timing) {

            timer += Time.deltaTime;

            if (timer >= timeTilEvent) {

                timing = false;

                timedEvent.Invoke();
            }
        }
	}
}
