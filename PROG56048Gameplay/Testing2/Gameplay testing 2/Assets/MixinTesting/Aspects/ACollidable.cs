using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class ACollidable : MonoBehaviour {

    private List<GameObject> collidedWith = new List<GameObject>();

    public string interactsWith;
    
    public UnityEvent onInteraction;

    public void OnCollisionEnter(Collision collision) {

        collidedWith.Add(collision.gameObject);

        if (collision.gameObject.GetComponent(interactsWith)) {

            if (onInteraction != null) {

                onInteraction.Invoke();
            }
        }
    }

    public void OnCollisionExit(Collision collision) {

        collidedWith.Remove(collision.gameObject);
    }

    public Component getObjectOfType(System.Type type) {

        Component found = null;

        foreach (GameObject go in collidedWith) {
            
            if (found = go.GetComponent(type)){

                return found;
            }
        }

        return null;
    }

    public List<Component> getObjectsOfType(System.Type type) {

        List<Component> hits = new List<Component>();

        foreach (GameObject go in collidedWith) {

            Component[] found = go.GetComponentsInChildren(type);

            if (found.Length > 0) {

                foreach (Component f in found) {

                    hits.Add(f);
                }
            }
        }

        return hits;
    }
}
