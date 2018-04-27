using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class MultiEventTrigger : MonoBehaviour {

    public enum Mode {

        Trigger,
        Collision
    }
    public Mode mode = Mode.Collision;

    public UnityEvent enterEvents;
    public UnityEvent stayEvents;
    public UnityEvent exitEvents;

    public List<Collider> ignoreThese = new List<Collider>();

    private void Start() {

        Collider me = GetComponent<Collider>();

        foreach (Collider c in ignoreThese) {

            Physics.IgnoreCollision(me, c);
        }
    }

    private void OnCollisionEnter(Collision collision) {
        Debug.Log("Kill me now");
        if (enterEvents != null && mode == Mode.Collision) {
            Debug.Log("Kill me harder");
            enterEvents.Invoke();
        }
    }

    private void OnCollisionStay(Collision collision) {

        if (stayEvents != null && mode == Mode.Collision) {

            stayEvents.Invoke();
        }
    }

    private void OnCollisionExit(Collision collision) {
        Debug.Log("Eat me bitch");
        if (exitEvents != null && mode == Mode.Collision) {
            Debug.Log("Eat me harder");
            exitEvents.Invoke();
        }
    }

    private void OnTriggerEnter(Collider other) {

        if (enterEvents != null && mode == Mode.Trigger) {

            enterEvents.Invoke();
        }
    }

    private void OnTriggerStay(Collider other) {

        if (stayEvents != null && mode == Mode.Trigger) {

            stayEvents.Invoke();
        }
    }

    private void OnTriggerExit(Collider other) {

        if (exitEvents != null && mode == Mode.Trigger) {

            exitEvents.Invoke();
        }
    }
}
