using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FireTrapFireTrigger : MonoBehaviour {

    private void OnTriggerEnter2D(Collider2D collision) {

        PlayerMovement player = collision.gameObject.GetComponent<PlayerMovement>();

        if (player != null) {

            player.kill();
        }
    }
}
