using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TriggerCondition : Condition {

    public enum TriggerMode {

        Enter,
        Exit,
        Stay
    }

    public TriggerMode mode = TriggerMode.Enter;

    public List<string> collidesWith;

    private List<GameObject> collideList = new List<GameObject>();

    private bool triggered = false;
    
    void OnTriggerEnter(Collider other) {
        
        if (checkTriggerCondition(other.gameObject)) {

            if (mode == TriggerMode.Enter) {

                collideList.Add(other.gameObject);
            }

            if (collideList.Count > 0) {

                triggered = true;
            }
            else {

                triggered = false;
            }
        }
    }

    void OnTriggerExit(Collider other) {

        if (checkTriggerCondition(other.gameObject)) {

            if (mode == TriggerMode.Exit) {

                triggered = true;
            }
            else {

                collideList.Remove(other.gameObject);

                if (collideList.Count > 0) {

                    triggered = true;
                }
                else {

                    triggered = false;
                }
            }
        }
    }

    void OnTriggerStay(Collider other) {

        if (checkTriggerCondition(other.gameObject)) {

            if (mode == TriggerMode.Stay) {

                if (collideList.Contains(other.gameObject)) {

                    collideList.Add(other.gameObject);
                }
            }

            if (collideList.Count > 0) {

                triggered = true;
            }
            else {

                triggered = false;
            }
        }
    }
    
    override public bool condition() {

        return triggered;
    }

    private bool checkTriggerCondition(GameObject collided) {

        if (collidesWith.Count == 0) {

            return true;
        }
        
        foreach (string id in collidesWith) {

            if (collided.GetComponent(id) != null) {

                return true;
            }
        }

        return false;
    }
}
