using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DisplayMgr : MonoBehaviour {

    private Text txtInGame;
    private Text txtOnScreenScore;
    private Text txtOnScreenWinMsg;

    private bool playerWon;

    public static DisplayMgr This;

    public GameObject inGameDisplay;
    public GameObject onScreenDisplay;
    public GameObject onScreenWinDisplay;

	// Use this for initialization
	void Start () {
		
        if (This == null) {

            This = this;
        }

        if (inGameDisplay != null && onScreenDisplay != null && onScreenWinDisplay != null) {

            txtInGame = inGameDisplay.GetComponent<Text>();
            txtOnScreenScore = onScreenDisplay.GetComponent<Text>();
            txtOnScreenWinMsg = onScreenWinDisplay.GetComponent<Text>();
        }
        else {

            Debug.Log("DisplayMgr: Error on startup, no displays attached.");
        }

        playerWon = false;
    }

    public void SetPlayerWon(bool w) {

        playerWon = w;
    }

    public void UpdateText(int num) {
        
        if (txtInGame != null) {

            txtInGame.text = "" + num;
        }
        else {

            Debug.Log("DisplayMgr: Can't update text component, in game display reference missing");
        }

        if (txtOnScreenScore != null) {

            txtOnScreenScore.text = "Score = " + num;
        }
        else {

            Debug.Log("DisplayMgr: Can't update text component, on screen display reference missing");
        }

        if (txtOnScreenWinMsg != null && playerWon == true) {

            txtOnScreenWinMsg.text = "PLAYER WON!!";
        }
        else if (txtOnScreenWinMsg == null) {

            Debug.Log("DisplayMgr: Can't update text component, on screen display winner reference missing");
        }
    }

    // Update is called once per frame
    void Update () {
		
	}
}
