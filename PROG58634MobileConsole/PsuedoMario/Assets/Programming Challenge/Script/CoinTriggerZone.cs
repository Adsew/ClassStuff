using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CoinTriggerZone : MonoBehaviour {
    
    public void OnTriggerEnter2D(Collider2D other) {

        if (other.tag == "Player") {

            ScoreManager.This.updateScore(1);

            Destroy(gameObject);
        }
    }
}
