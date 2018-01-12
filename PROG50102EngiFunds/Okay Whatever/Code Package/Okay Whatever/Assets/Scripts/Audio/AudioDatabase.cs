using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "NewAudioDataBase", menuName = "AudioDatabase", order = 1)]
public class AudioDatabase : ScriptableObject
{
    [SerializeField]
    private List<AudioData> audioClips = new List<AudioData>();
    private AudioSource audioSource;

    public void SetAudioSource(AudioSource source)
    {
        audioSource = source;
    }

    public void PlayRandom()
    {
        if (audioClips.Count <= 0)
        {
            Debug.LogError("Cannot play random sound with no audio data");
            return;
        }

        if (audioSource == null)
        {
            Debug.LogError("Cannot play random sound without audio source");
            return;
        }

        AudioData audioData = audioClips[Random.Range(0, audioClips.Count - 1)];
        audioData.Play(audioSource);
    }

    public void PlayByName(string name)
    {
        foreach (AudioData data in audioClips)
        {
            if (data.AudioName == name)
            {
                data.Play(audioSource);
                return;
            }
        }
    }
}
