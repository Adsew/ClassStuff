using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreManager : MonoBehaviour {

    public static ScoreManager This;

    public Text scoreDisplay;

    private int score;

    // Use this for initialization
    void Start () {
		
        if (This == null) {

            This = this;
        }
	}
	
	public void updateScore(int amount) {

        score += amount;

        if (scoreDisplay != null) {

            scoreDisplay.text = "Score: " + score;
        }
    }
}
