using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class doggos3 : MonoBehaviour {
    public Image doggoRaw;
    public Sprite doggo;
    public AudioSource music;
    public AudioClip musicSpe;

    public void doggoChange()
    {
        doggoRaw.enabled = true;
        doggoRaw.sprite = doggo;
        music.Pause();
        music.clip = musicSpe;
        music.Play();
    }
}