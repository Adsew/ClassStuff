using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundMgr : MonoBehaviour {

    public static SoundMgr This;

    public List<AudioClip> fireSounds;
    public List<AudioClip> collisionSounds;
    public List<AudioClip> targetSounds;

    private AudioSource fireSrc;
    private AudioSource collisionSrc;
    private AudioSource targetSrc;

    // Use this for initialization
    void Start() {

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

        if (This == null) {
            This = this;
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

    // Update is called once per frame
    void Update () {
		
	}
}
