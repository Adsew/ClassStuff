using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundMgr : MonoBehaviour {

    public static SoundMgr This;

    [Range(10.0f, 200.0f)]
    public float playerEarshot = 100.0f;

    public AudioClip backgroundSound;
    public AudioClip startSound;
    public AudioClip endSound;

    public List<AudioClip> cannonFireSounds;
    public List<AudioClip> gunFireSounds;
    public List<AudioClip> collisionSounds;
    public List<AudioClip> explosionSounds;

    private AudioSource backgroundSoundSrc;
    private AudioSource notificationSoundSrc;

    // Use this for initialization
    void Start() {

        if (This == null) {

            This = this;
        }

        // Set sources
        if (notificationSoundSrc == null) {

            notificationSoundSrc = this.gameObject.AddComponent<AudioSource>();
            notificationSoundSrc.playOnAwake = false;
        }
        if (backgroundSoundSrc == null) {

            backgroundSoundSrc = this.gameObject.AddComponent<AudioSource>();
            backgroundSoundSrc.playOnAwake = false;
        }
    }

    public void PlayBackgroundSound() {

        if (backgroundSound != null) {

            backgroundSoundSrc.clip = backgroundSound;
            backgroundSoundSrc.loop = true;
            backgroundSoundSrc.Play(0);
        }
    }

    public void StopBackgroundSound() {

        if (backgroundSoundSrc.isPlaying) {

            backgroundSoundSrc.Stop();
        }
    }

    public void PlayStartGameSound() {

        if (backgroundSound != null) {

            notificationSoundSrc.clip = startSound;
            notificationSoundSrc.Play(0);
        }
    }

    public void PlayEndGameSound() {

        if (backgroundSound != null) {

            notificationSoundSrc.clip = endSound;
            notificationSoundSrc.Play(0);
        }
    }

    public void PlayRandomCannonFireSound(AudioSource src) {
        
        if (cannonFireSounds.Count > 0) {
            
            int index = Random.Range(0, cannonFireSounds.Count);

            if (cannonFireSounds[index] != null) {
                
                src.clip = cannonFireSounds[index];
                src.PlayOneShot(src.clip);
            }
        }
    }

    public void PlayRandomGunFireSound(AudioSource src) {

        if (gunFireSounds.Count > 0) {

            int index = Random.Range(0, gunFireSounds.Count);

            if (gunFireSounds[index] != null) {

                src.clip = gunFireSounds[index];
                src.PlayOneShot(src.clip);
            }
        }
    }

    public void PlayRandomCollisionSound(AudioSource src) {
        
        if (collisionSounds.Count > 0 ) {
            
            int index = Random.Range(0, collisionSounds.Count);
            
            if (collisionSounds[index] != null) {

                src.clip = collisionSounds[index];
                src.PlayOneShot(src.clip);
            }
        }
    }

    public void PlayRandomExplosionSound(AudioSource src) {

        if (explosionSounds.Count > 0) {

            int index = Random.Range(0, explosionSounds.Count);

            if (explosionSounds[index] != null) {

                src.clip = explosionSounds[index];
                src.PlayOneShot(src.clip);
            }
        }
    }

    // For other classes trying to play sounds
    // Each class can determine if this is needed when playing a sound
    public bool InEarshotOfPlayer(Vector3 soundPos) {

        if (Vector3.Magnitude(soundPos - Player.This.pGameObject.transform.position) <= playerEarshot) {

            return true;
        }

        return false;
    }

    // Update is called once per frame
    void Update () {
		
	}
}
