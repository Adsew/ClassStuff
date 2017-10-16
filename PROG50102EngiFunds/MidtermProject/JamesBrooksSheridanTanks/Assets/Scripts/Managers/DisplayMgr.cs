using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DisplayMgr : MonoBehaviour {

    private Text onScreenMsgLog;
    private Text onScreenScoreText;

    private bool playerWon;

    public static DisplayMgr This;

    public GameObject onScreenMsgLogDisplay;
    public GameObject onScreenScoreDisplay;

	// Use this for initialization
	void Start () {
		
        if (This == null) {

            This = this;
        }

        if (onScreenMsgLogDisplay != null && onScreenScoreDisplay != null) {

            onScreenMsgLog = onScreenMsgLogDisplay.GetComponent<Text>();
            onScreenScoreText = onScreenScoreDisplay.GetComponent<Text>();
        }
        else {

            Debug.Log("DisplayMgr: Error on startup, no displays attached.");
        }

        playerWon = false;
    }

    public void SetPlayerWon(bool w) {

        playerWon = w;
    }

    public void UpdateText(string msg) {
        
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

    // Update is called once per frame
    void Update () {
		
	}
}
