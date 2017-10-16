using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundMgr : MonoBehaviour {

    public static SoundMgr This;

    [Range(10.0f, 100.0f)]
    public float playerEarshot = 30.0f;

    public List<AudioClip> fireSounds;
    public List<AudioClip> collisionSounds;
    public List<AudioClip> targetSounds;

    private AudioSource fireSrc;
    private AudioSource collisionSrc;
    private AudioSource targetSrc;

    // Use this for initialization
    void Start() {

        if (This == null) {

            This = this;
        }

        // Set sources
        if (fireSrc == null) {

            fireSrc = this.gameObject.AddComponent<AudioSource>();
            fireSrc.playOnAwake = false;
        }
        if (collisionSrc == null) {

            collisionSrc = this.gameObject.AddComponent<AudioSource>();
            collisionSrc.playOnAwake = false;
        }
        if (targetSrc == null) {

            targetSrc = this.gameObject.AddComponent<AudioSource>();
            targetSrc.playOnAwake = false;
        }
    }

    public void PlayRandomFireSound() {
        
        if (fireSounds.Count > 0) {
            
            int index = Random.Range(0, fireSounds.Count);

            if (fireSounds[index] != null) {
                
                fireSrc.clip = fireSounds[index];
                fireSrc.PlayOneShot(fireSrc.clip);
            }
        }
    }

    public void PlayRandomCollisionSound() {
        
        if (collisionSounds.Count > 0 ) {
            
            int index = Random.Range(0, collisionSounds.Count);
            
            if (collisionSounds[index] != null) {

                collisionSrc.clip = collisionSounds[index];
                collisionSrc.PlayOneShot(collisionSrc.clip);
            }
        }
    }

    public void PlayRandomTargetSound() {

        if (targetSounds.Count > 0) {

            int index = Random.Range(0, targetSounds.Count);

            if (targetSounds[index] != null) {

                targetSrc.clip = targetSounds[index];
                targetSrc.PlayOneShot(targetSrc.clip);
            }
        }
    }

    // For other classes trying to play sounds
    // Each class can determine if this is needed when playing a sound
    public bool InEarshotOfPlayer(Vector3 soundPos) {

        if (Vector3.Magnitude(soundPos - PlayerStats.This.player.transform.position) <= playerEarshot) {

            return true;
        }

        return false;
    }

    // Update is called once per frame
    void Update () {
		
	}
}
