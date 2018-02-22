using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MPlaySound : MonoBehaviour {

    private AudioSource source;

    public AudioClip sound;

    public void playClipOneShot() {

        if (source != null) {

            source.PlayOneShot(sound);
        }
    }

    // Use this for initialization
    void Start () {
		
        if (source == null) {

            source = GetComponent<AudioSource>();
        }
	}
}
