using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Audio;
using UnityEngine.UI;

public class Volume : MonoBehaviour
{
    public Slider SlMusics;
    public Toggle tgMusic;
    public AudioSource Musique;
    public AudioMixer audioMix;

    void Start()
    {
        if((PlayerPrefs.GetInt("mute") == 1) && (Musique != null))
        {
            Musique.GetComponent<AudioSource>();
            Musique.Stop();
            Global.musiqueSTOP = true;
            SlMusics.interactable = false;
            SlMusics.value = PlayerPrefs.GetFloat("vol");
            tgMusic.isOn = false;
        }
        else
        {

            if (SlMusics != null)
            {

                SlMusics.value = PlayerPrefs.GetFloat("vol");
            }
        }

    }

    public void setVolume(float volume)
    {
        audioMix.SetFloat("volume", volume);
        PlayerPrefs.SetFloat("vol", SlMusics.value);
    }

    public void mutetoggleM()
    {
        if (!tgMusic.isOn)
        {
            Musique.Pause();
            SlMusics.interactable = false ;
            PlayerPrefs.SetInt("mute", 1);
        }
         else
        {
            Musique.Play();
            SlMusics.interactable = true ;
            PlayerPrefs.SetInt("mute", 0);
        }
    }
 }
