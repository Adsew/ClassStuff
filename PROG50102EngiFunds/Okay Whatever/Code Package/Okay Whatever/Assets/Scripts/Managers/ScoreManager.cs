using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScoreManager : MonoBehaviour
{

    private int mScore;

    public ScoreText scoreText;

    private int mPickScore = 10;
    private int mJumpOverScore = 10;

    //-----------------------------
    //  EnemyManager Singleton
    //
    private static ScoreManager _instance;
    public static ScoreManager Instance
    {
        get { return _instance; }
    }


    // Use this for initialization
    void Start()
    {
        if (_instance == null)
        {
            mScore = 0;
            scoreText.UpdateScore(mScore);
            _instance = this;
        }
        else
        {
            Destroy(this);
        }
    }

    public void addScore(int pts)
    {
        mScore += pts;
        scoreText.UpdateScore(mScore);
    }
    public void scorePickupable()
    {
        mScore += mPickScore;
        scoreText.UpdateScore(mScore);
    }

    public void scoreJumpOver()
    {
        mScore += mJumpOverScore;
        scoreText.UpdateScore(mScore);
    }

    public void resetScore()
    {
        mScore = 0;
        scoreText.UpdateScore(mScore);
    }

    public int getScore()
    {
        return mScore;
    }

    public void setPickScore(int pickupableScore)
    {
        mPickScore = pickupableScore;
    }

    public void setJumpOverScore(int jumpScpre)
    {
        mJumpOverScore = jumpScpre;
    }
}
