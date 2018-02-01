using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DeathZoneTrigger : MonoBehaviour {
    
    public void OnTriggerEnter2D(Collider2D other) {
        
        if (other.tag == "Player") {

            IsPlayer player = other.GetComponent<IsPlayer>();

            if (player != null) {

                player.die();
            }
        }
    }
}
