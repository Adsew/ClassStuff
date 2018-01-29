using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

[RequireComponent(typeof(Rigidbody))]
public class ACollidable : MonoBehaviour {

    public string interactsWith;

    public UnityEvent onInteraction;

    public void OnCollisionEnter(Collision collision) {
        
        if (collision.gameObject.GetComponent(interactsWith)) {

            if (onInteraction != null) {

                onInteraction.Invoke();
            }
        }
    }
}
