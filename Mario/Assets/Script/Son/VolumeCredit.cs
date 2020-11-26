using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Audio;

public class VolumeCredit : MonoBehaviour
{
    public AudioSource music;
    public AudioMixer audioMix;

    // Start is called before the first frame update
    void Start()
    {
        audioMix.SetFloat("volume", PlayerPrefs.GetFloat("vol"));

        if (PlayerPrefs.GetInt("mute") == 1)
        {
            music.Pause();
        }
        else
        {
            music.Play();
        }
    }

    // Update is called once per frame
    void Update()
    {
        audioMix.SetFloat("volume", PlayerPrefs.GetFloat("vol"));

        if (PlayerPrefs.GetInt("mute") == 1)
        {
            music.Pause();
        }
    }
}
