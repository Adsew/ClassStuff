using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsPlayer : MonoBehaviour {

    public GameObject respawnLocation;

    public AudioClip deathSound;
    public AudioClip winSound;

    private AudioSource myAudioSource;

    private void Start() {
        
        if (myAudioSource == null) {

            myAudioSource = GetComponent<AudioSource>();
        }
    }

    public void die() {

        if (respawnLocation != null) {

            transform.position = respawnLocation.transform.position;
        }

        if (deathSound != null && myAudioSource != null) {
            
            myAudioSource.PlayOneShot(deathSound);
        }
    }

    public void win() {

        if (winSound != null && myAudioSource != null) {

            myAudioSource.PlayOneShot(winSound);
        }
    }
}
