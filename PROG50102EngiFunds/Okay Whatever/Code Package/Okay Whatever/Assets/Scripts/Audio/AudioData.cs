using UnityEngine;

[CreateAssetMenu(fileName = "NewAudioData", menuName = "AudioData", order = 1)]
public class AudioData : ScriptableObject
{
    [SerializeField]
    private string audioName;
    public string AudioName
    {
        get { return audioName; }
    }
    public AudioClip audioClip;
    [Range(0.0f, 1.0f)]
    public float volume;
    [Range(0.5f, 2.0f)]
    public float pitch;
    public bool loop = false;

    public void Play(AudioSource source)
    {
        if (source != null)
        {
            source.playOnAwake = false;
            source.loop = loop;
            source.pitch = pitch;
            if (loop == true)
            {
                source.clip = audioClip;
                source.volume = volume;
                source.Play();
            }
            else
            {
                source.PlayOneShot(audioClip, volume);
            }
        }
    }

    public void Stop(AudioSource source)
    {
        if (source != null)
        {
            source.Stop();
        }
    }
}
