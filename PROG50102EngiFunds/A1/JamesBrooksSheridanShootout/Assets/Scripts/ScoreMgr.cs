using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScoreMgr : MonoBehaviour {

    public static ScoreMgr This;

    private int score;

	// Use this for initialization
	void Start () {
		
        if (This == null) {

            This = this;
        }
	}

    public void IncScore(int n)
    {
        score = score + n;

        if (DisplayMgr.This != null) {

            DisplayMgr.This.UpdateText(score);
        }
        else {

            Debug.Log("ScoreMgr: Cant update score. DisplayMgr does not exist.");
        }
    }

    // Update is called once per frame
    void Update () {
		
	}
}
