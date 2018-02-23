using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreManager : MonoBehaviour {

    public static ScoreManager This = null;

    public int maxScore = 5;

    private Text text = null;

    private int score;

	// Use this for initialization
	void Start () {
		
        if (This == null) {

            This = this;
        }

        if (text == null) {

            text = GetComponent<Text>();
        }
	}
	
    public void updateScore(int toAdd) {

        score += toAdd;

        if (text != null) {

            text.text = "Found: " + score + " / " + maxScore;
        }
    }
}
