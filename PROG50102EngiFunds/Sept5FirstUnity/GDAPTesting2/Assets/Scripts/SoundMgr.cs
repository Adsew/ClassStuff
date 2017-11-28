using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundMgr : MonoBehaviour {
    
    public List<AudioClip> FireSounds;
    public List<AudioClip> Explosions;
    
    private AudioSource asource;

    public AudioClip DribbleSound;
    private AudioSource DribbleSource;

    public static SoundMgr This;
    

	// Use this for initialization
	void Start () {

        if (asource == null)
        {
            asource = this.gameObject.AddComponent<AudioSource>();
            asource.playOnAwake = false;
        }
        
        if (DribbleSource == null) {

            DribbleSource = this.gameObject.AddComponent<AudioSource>();
            DribbleSource.playOnAwake = false;
        }

        if (This == null)
        {
            This = this;
        }
	}
	

    public void PlayRandomFireSound()
    {
        int index = Random.Range(0, FireSounds.Count);
        asource.clip = FireSounds[index];
        asource.PlayOneShot(asource.clip);
    }

    public void PlayDribble() {
        
        DribbleSource.clip = DribbleSound;
        DribbleSource.PlayOneShot(DribbleSource.clip);
    }

    public void PlayRandomExplosionSound()
    {
        int index = Random.Range(0, Explosions.Count);
        asource.clip = Explosions[index];
        asource.PlayOneShot(asource.clip);
    }

    // Update is called once per frame
    void Update () {
		
	}
}
