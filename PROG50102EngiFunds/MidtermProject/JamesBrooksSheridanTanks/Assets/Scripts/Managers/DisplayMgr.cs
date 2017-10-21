using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DisplayMgr : MonoBehaviour {

    private GameObject currentScreen;

    private Text onScreenMsgLog;
    private Text onScreenScoreText;
    private Text onScreenHealthText;

    private Text onScreenFinalScoreText;
    
    public static DisplayMgr This;
    
    public GameObject titleScreen;

    public GameObject deathScreen;

    public GameObject hudScreen;
    public GameObject onScreenMsgLogDisplay;
    public GameObject onScreenScoreDisplay;
    public GameObject onScreenHealthDisplay;

    public GameObject onScreenFinalScoreDisplay;

    // Use this for initialization
    void Start () {
		
        if (This == null) {

            This = this;
        }

        if (onScreenMsgLogDisplay != null 
            || onScreenScoreDisplay != null
            || onScreenHealthDisplay != null
            || onScreenFinalScoreDisplay != null) {

            onScreenMsgLog = onScreenMsgLogDisplay.GetComponent<Text>();
            onScreenScoreText = onScreenScoreDisplay.GetComponent<Text>();
            onScreenHealthText = onScreenHealthDisplay.GetComponent<Text>();
            onScreenFinalScoreText = onScreenFinalScoreDisplay.GetComponent<Text>();
        }
        else {

            Debug.Log("DisplayMgr: Error on startup, one or more text displays not attached.");
        }


        if (titleScreen != null && hudScreen != null && deathScreen != null) {

            currentScreen = titleScreen;    // Start of game at title screen
            hudScreen.SetActive(false);
            deathScreen.SetActive(false);
            currentScreen.SetActive(true);
        }
        else {

            Debug.Log("DisplayMgr: Error on startup, missing title screen or HUD screen.");
        }
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

    public void UpdatePlayerHealth(int num) {

        if (onScreenHealthText != null) {

            onScreenHealthText.text = "Hull Integrity: " + num;
        }
        else {

            Debug.Log("DisplayMgr: Can't update player health, on screen health reference missing");
        }
    }

    public void UpdateFinalScore() {

        onScreenFinalScoreText.text = onScreenScoreText.text;
    }

    // Swap between screens depending on game state
    private void ScreenSwapUpdate() {

        if (GameStateMgr.This.gameIsPlaying && currentScreen != hudScreen) {

            currentScreen.SetActive(false);
            currentScreen = hudScreen;
            currentScreen.SetActive(true);
        }
        else if (GameStateMgr.This.gameIsOver && currentScreen != deathScreen) {

            currentScreen.SetActive(false);
            currentScreen = deathScreen;
            currentScreen.SetActive(true);
        }
    }

    // Update is called once per frame
    void Update () {

        ScreenSwapUpdate();
	}
}
