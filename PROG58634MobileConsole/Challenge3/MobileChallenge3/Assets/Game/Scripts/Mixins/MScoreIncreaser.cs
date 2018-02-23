using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MScoreIncreaser : MonoBehaviour {

    public int scoreWorth = 1;

    public void increaseScore() {

        ScoreManager.This.updateScore(scoreWorth);
    }
}
