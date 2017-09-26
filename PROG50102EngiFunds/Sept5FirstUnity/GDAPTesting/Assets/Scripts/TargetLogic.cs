using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TargetLogic : MonoBehaviour {

    public void OnCollisionEnter(Collision col)
    {
        if (col.gameObject != null)
        {
            if (col.gameObject.GetComponent<IsProjectile>() != null) //fix this
            {
                Destroy(this.gameObject); // this is the script component

                // need to incrasescore now
                ScoreMgr.This.IncScore(1);
                SoundMgr.This.PlayRandomExplosionSound();
            }
        }

        //Somehting hit me do somehting
        Debug.Log("I was hit by: " + col.gameObject.name);
    }

    // Use this for initialization
    void Start () {
		

	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
