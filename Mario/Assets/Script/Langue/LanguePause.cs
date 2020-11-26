using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class LanguePause : MonoBehaviour
{
    public Text labelTitrePause;

    public Text btnContinuer;
    public Text btnParametre;
    public Text btnMenuPrincipal;

    // Use this for initialization
    void Start()
    {
        if (PlayerPrefs.GetInt("lang") == 0)
        {
            //Sc Pause FR
            labelTitrePause.text = "Pause";
            btnContinuer.text = "Continuer";
            btnParametre.text = "Parametre";
            btnMenuPrincipal.text = "Menu Principal";
        }
        else
        {
            //Sc Pause ENG
            labelTitrePause.text = "Paused";
            btnContinuer.text = "Continue";
            btnParametre.text = "Setting";
            btnMenuPrincipal.text = "Main Menu";
        }
    }
}
