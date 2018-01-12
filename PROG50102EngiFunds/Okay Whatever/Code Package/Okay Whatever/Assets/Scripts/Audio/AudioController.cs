using UnityEngine;

[RequireComponent(typeof(AudioSource))]
public class AudioController : MonoBehaviour
{
    public AudioData audioData;
    private AudioSource _audioSource;

    private void Start()
    {
        _audioSource = GetComponent<AudioSource>();
        Debug.Assert(_audioSource != null);
    }

    public void PlayClip()
    {
        if (audioData != null)
        {
            if (_audioSource == null)
            {
                _audioSource = GetComponent<AudioSource>();
            }
            audioData.Play(_audioSource);
        }
    }
}
