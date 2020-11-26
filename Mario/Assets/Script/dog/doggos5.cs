using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class doggos5 : MonoBehaviour {
    public Image doggoRaw;
    public Sprite doggo;
    public AudioSource music;
    public AudioClip musicSpe;

    private void Start()
    {
        doggoRaw.enabled = false;
    }
    public void doggoChange()
    {
        doggoRaw.enabled = true;
        doggoRaw.sprite = doggo;
        music.Pause();
        music.clip = musicSpe;
        music.Play();
    }
}