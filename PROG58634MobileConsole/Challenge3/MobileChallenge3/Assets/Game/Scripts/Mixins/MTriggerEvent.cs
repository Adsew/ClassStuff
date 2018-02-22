using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class MTriggerEvent : MonoBehaviour {

    public enum Mode {

        Enter,
        Exit
    }

    public Mode mode;

    public UnityEvent triggerEvent;

    private void OnTriggerEnter2D(Collider2D other) {

        if (mode == Mode.Enter) {

            triggerEvent.Invoke();
        }
    }

    private void OnTriggerExit2D(Collider2D collision) {

        if (mode == Mode.Exit) {

            triggerEvent.Invoke();
        }
    }
}
