using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MTimedDestroy : MonoBehaviour {

    private float timer = 0;

    public float timeTilDestroy = 10.0f;
    
	// Update is called once per frame
	void Update () {

        timer += Time.deltaTime;

        if (timer >= timeTilDestroy) {

            Destroy(gameObject);
        }
	}
}
