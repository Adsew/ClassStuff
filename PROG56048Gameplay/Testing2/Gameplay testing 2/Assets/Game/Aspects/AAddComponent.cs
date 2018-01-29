using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AAddComponent : MonoBehaviour {

    public GameObject applyComponentTo;

	public void addComponentToTarget(Component comp) {

        applyComponentTo.AddComponent(comp.GetType());
    }
}
