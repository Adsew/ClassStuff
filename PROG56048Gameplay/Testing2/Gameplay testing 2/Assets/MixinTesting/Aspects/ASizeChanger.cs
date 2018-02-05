using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ASizeChanger : MonoBehaviour {

    public Vector3 sizeMultiplier = new Vector3();

	// Use this for initialization
	void Start () {

        Vector3 scale = transform.localScale;

        scale.x *= sizeMultiplier.x;
        scale.y *= sizeMultiplier.y;
        scale.z *= sizeMultiplier.z;

        transform.localScale = scale;
    }

    private void OnDestroy() {

        Vector3 scale = transform.localScale;

        scale.x /= sizeMultiplier.x;
        scale.y /= sizeMultiplier.y;
        scale.z /= sizeMultiplier.z;

        transform.localScale = scale;
    }
}
