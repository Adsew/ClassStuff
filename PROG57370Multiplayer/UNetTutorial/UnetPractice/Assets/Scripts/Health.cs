using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;
using UnityEngine.UI;

public class Health : NetworkBehaviour {

    public RectTransform healthDisplay = null;

    public const int maxHealth = 100;

    [SyncVar(hook = "OnChangeHealth")]
    public int currentHealth = maxHealth;

    public bool destroyOnDeath = false;

    public void TakeDamage(int amount) {

        if (!isServer) {

            return;
        }

        currentHealth -= amount;

        if (currentHealth <= 0) {

            if (destroyOnDeath) {

                Destroy(gameObject);
            }
            else {

                currentHealth = maxHealth;

                RpcRespawn();
            }
        }
    }

    private void OnChangeHealth(int currentHealth) {

        healthDisplay.sizeDelta = new Vector2(currentHealth, healthDisplay.sizeDelta.y);
    }

    [ClientRpc]
    private void RpcRespawn() {

        if (isLocalPlayer) {

            // move back to zero location
            transform.position = Vector3.zero;
        }
    }
}
