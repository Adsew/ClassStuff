using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameStateMgr : MonoBehaviour {

    public static GameStateMgr This;

    public double gameTime { get; private set; }

    public bool gameIsPlaying { get; private set; }

    // Use this for initialization
    void Start () {

        if (This == null) {

            This = this;
        }

        gameTime = 0.0f;
        gameIsPlaying = false;
	}
	
    public void startTiming() {

        gameIsPlaying = true;
    }

    private void timerUpdate() {

        if (gameIsPlaying) {

            gameTime += Time.deltaTime;
        }
    }

	// Update is called once per frame
	void Update () {

        timerUpdate();
	}
}
