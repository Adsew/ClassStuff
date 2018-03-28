using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner.Runtime;

public class MouseMakeNoise : MonoBehaviour {
    
    private BehaviorTree tree = null;
    private SharedTransformList sounds = null;

    void Start() {

        tree = GetComponent<BehaviorTree>();

        if (tree != null) {

            sounds = (SharedTransformList)tree.GetVariable("soundLocations");
        }
    }

    // Update is called once per frame
    void Update () {
		
        if (Input.GetMouseButtonDown(0)) {

            if (tree != null) {

                RaycastHit ray;

                if (Physics.Raycast(Camera.main.ScreenPointToRay(Input.mousePosition), out ray, 100)) {
                    
                    GameObject go = new GameObject("Noise");
                    
                    if (sounds != null && go != null) {

                        go.transform.position = ray.point;

                        sounds.Value.Add(go.transform);
                    }
                }
            }
        }
	}

    
}
