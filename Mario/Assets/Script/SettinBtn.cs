using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class SettinBtn : MonoBehaviour
{
    public Slider slMusic;
    public Slider slSensi;
    public Toggle tgMusics;
    public Toggle tgDroitier;
    public Toggle tgGaucher;

    public AudioSource musics;

    // Start is called before the first frame update
    void Start()
    {
        if (PlayerPrefs.GetInt("rightLeft") == 1)
        {
            tgDroitier.isOn = true;
        }
        else
        {
            tgGaucher.isOn = true;
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (tgDroitier.isOn == true)
        {
            Global.isGaucher = false;
            PlayerPrefs.SetInt("rightLeft", 1);
        }
        else
        {
            Global.isGaucher = true;
            PlayerPrefs.SetInt("rightLeft", 0);
        }
    }

    public void btnRetabli()
    {
        musics.PlayScheduled(0);
        slMusic.value = 0;
        tgMusics.isOn = true;
        slSensi.value = 50;
        tgDroitier.isOn = true;
    }
}
