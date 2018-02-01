using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WinZoneTrigger : MonoBehaviour {

    public GameObject winScreen;

    public void OnTriggerEnter2D(Collider2D other) {

        if (other.tag == "Player") {

            IsPlayer player = other.GetComponent<IsPlayer>();

            if (player != null) {

                if (winScreen != null) {

                    winScreen.SetActive(true);
                }

                player.win();
            }
        }
    }
}
