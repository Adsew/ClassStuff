using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameStateMgr : MonoBehaviour {

    public static GameStateMgr This;

    public float gameTime { get; private set; }

    public bool gameIsPlaying { get; private set; }

    // Use this for initialization
    void Start () {

        if (This == null) {

            This = this;
        }

        gameTime = 0.0f;
        gameIsPlaying = false;

        Player.This.LockControls(true);
	}
	
    public void StartGame() {
        
        gameIsPlaying = true;

        EnemySpawnMgr.This.GameStartSpawns();
        Player.This.pCamera.SetFocusPlayer();
        Player.This.LockControls(false);
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
