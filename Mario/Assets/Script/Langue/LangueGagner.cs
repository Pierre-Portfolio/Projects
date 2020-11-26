using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class LangueGagner : MonoBehaviour
{
    public Text labelTitreGagner;
    public Text labelTemps;
    public Text labelScore;
    public Text btnMenu;
    public Text labelNbCoins;
    public Text labelTmps;

    // Use this for initialization
    void Start()
    {
        labelNbCoins.text = Global.score+"";
        labelTmps.text = Global.temps+"";
        if (PlayerPrefs.GetInt("lang") == 0)
        {
            //Sc Gagne FR
            labelTitreGagner.text = "Tu as gagner";
            labelScore.text = "Score final";
            labelTemps.text = "votre temps";
            btnMenu.text = "Menu Pincipal";
        }
        else
        {
            //Sc Gagne ENG
            labelTitreGagner.text = "you won";
            labelScore.text = "final score";
            labelTemps.text = "your time";
            btnMenu.text = "Main Menu";
        }
    }
}
