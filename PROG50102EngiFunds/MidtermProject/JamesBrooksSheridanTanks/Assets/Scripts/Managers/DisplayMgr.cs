using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DisplayMgr : MonoBehaviour {

    private GameObject currentScreen;

    private Text onScreenMsgLog;
    private Text onScreenScoreText;

    private bool playerWon;

    public static DisplayMgr This;
    
    public GameObject titleScreen;

    public GameObject hudScreen;
    public GameObject onScreenMsgLogDisplay;
    public GameObject onScreenScoreDisplay;

	// Use this for initialization
	void Start () {
		
        if (This == null) {

            This = this;
        }

        if (onScreenMsgLogDisplay != null || onScreenScoreDisplay != null) {

            onScreenMsgLog = onScreenMsgLogDisplay.GetComponent<Text>();
            onScreenScoreText = onScreenScoreDisplay.GetComponent<Text>();
        }
        else {

            Debug.Log("DisplayMgr: Error on startup, no text displays attached.");
        }


        if (titleScreen != null && hudScreen != null) {

            currentScreen = titleScreen;    // Start of game at title screen
            hudScreen.SetActive(false);
            currentScreen.SetActive(true);
        }
        else {

            Debug.Log("DisplayMgr: Error on startup, missing title screen or HUD screen.");
        }
        
        playerWon = false;
    }

    public void SetPlayerWon(bool w) {

        playerWon = w;
    }

    public void UpdateMessage(string msg) {
        
        if (onScreenMsgLog != null) {

            onScreenMsgLog.text = msg;
        }
        else {

            Debug.Log("DisplayMgr: Can't update text component, message log reference missing");
        }
    }

    public void UpdateScore(int num) {

        if (onScreenScoreText != null) {

            onScreenScoreText.text = "Score = " + num;
        }
        else {

            Debug.Log("DisplayMgr: Can't update text component, on screen score reference missing");
        }
    }

    // Code can be made more complex with pause menus and such
    // But in this game it only needs to be simple
    private void ScreenSwapUpdate() {

        if (GameStateMgr.This.gameIsPlaying && currentScreen != hudScreen) {

            currentScreen.SetActive(false);
            currentScreen = hudScreen;
            currentScreen.SetActive(true);
        }
    }

    // Update is called once per frame
    void Update () {

        ScreenSwapUpdate();
	}
}
