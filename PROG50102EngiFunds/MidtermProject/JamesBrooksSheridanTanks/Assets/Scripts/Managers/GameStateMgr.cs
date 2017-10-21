using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameStateMgr : MonoBehaviour {

    public static GameStateMgr This;

    public GameObject playerPrefab;

    public Vector3 playerRespawnPos = new Vector3(158, 1, 134);

    public float gameTime { get; private set; }

    public bool gameIsPlaying { get; private set; }
    public bool gameIsOver { get; private set; }

    // Use this for initialization
    void Start () {

        if (This == null) {

            This = this;
        }

        gameTime = 0.0f;
        gameIsPlaying = false;
        gameIsOver = false;

        Player.This.LockControls(true);
	}
	
    public void StartGame() {
        
        gameIsPlaying = true;
        gameIsOver = false;

        gameTime = 0.0f;

        ScoreMgr.This.ResetScore();
        EnemySpawnMgr.This.GameStartSpawns();
        Player.This.RespawnPlayer(playerRespawnPos);
        Player.This.pCamera.SetFocusPlayer();
        Player.This.LockControls(false);
    }
    
    public void EndGame() {

        gameIsOver = true;
        gameIsPlaying = false;

        EnemySpawnMgr.This.ResetToBase();
        
        Player.This.LockControls(true);
        Player.This.pCamera.SetFocusSpline();

        DisplayMgr.This.UpdateFinalScore();
        DisplayMgr.This.UpdateMessage("Let's try that again. Back to difficulty 1.");
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
