using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScoreMgr : MonoBehaviour {

    public int score;

    // Use singleton pattern... gaurentee only one instance of the mgr class by making this static
    public static ScoreMgr This;


    public void IncScore(int n)
    {
        score += n;
    }

	// Use this for initialization
	void Start () {
		
        // Cache a reference of store mgr so there is only one
        if (This == null)
        {
            This = this;
        }
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
