using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundMgr : MonoBehaviour {

    public static SoundMgr This;

    [Range(10.0f, 200.0f)]
    public float playerEarshot = 100.0f;

    public AudioClip backgroundSound1;
    public AudioClip backgroundSound2;
    public AudioClip startSound;
    public AudioClip endSound;

    public List<AudioClip> cannonFireSounds;
    public List<AudioClip> gunFireSounds;
    public List<AudioClip> collisionSounds;
    public List<AudioClip> explosionSounds;

    private AudioSource backgroundSound1Src;
    private AudioSource backgroundSound2Src;
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
        if (backgroundSound1Src == null) {

            backgroundSound1Src = this.gameObject.AddComponent<AudioSource>();
            backgroundSound1Src.playOnAwake = false;
        }
        if (backgroundSound2Src == null) {

            backgroundSound2Src = this.gameObject.AddComponent<AudioSource>();
            backgroundSound2Src.playOnAwake = false;
        }
    }

    public void PlayBackgroundSound() {

        if (backgroundSound1 != null) {

            backgroundSound1Src.clip = backgroundSound1;
            backgroundSound1Src.loop = true;
            backgroundSound1Src.Play(0);
        }

        if (backgroundSound2 != null) {

            backgroundSound2Src.clip = backgroundSound2;
            backgroundSound2Src.loop = true;
            backgroundSound2Src.Play(0);
            backgroundSound2Src.volume = 0.0f;
        }
    }

    public void StopBackgroundSound() {

        if (backgroundSound1Src.isPlaying) {

            backgroundSound1Src.Stop();
        }

        if (backgroundSound2Src.isPlaying) {

            backgroundSound2Src.Stop();
        }
    }

    public void CrossFadeBackgroundSound(float cf) {

        if (cf >= 0.0f && cf <= 1.0f) {
            if (backgroundSound1Src != null && backgroundSound2Src != null) {

                backgroundSound1Src.volume = 1.0f - cf;
                backgroundSound2Src.volume = cf;
            }
        }
    }

    public void PlayStartGameSound() {

        if (startSound != null) {

            notificationSoundSrc.clip = startSound;
            notificationSoundSrc.Play(0);
        }
    }

    public void PlayEndGameSound() {

        if (endSound != null) {

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
