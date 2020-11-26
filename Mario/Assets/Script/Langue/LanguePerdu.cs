using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class LanguePerdu : MonoBehaviour
{
    public Text labelTitre;
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
            //Sc Perdu FR
            labelTitre.text = "Tu as perdu ...";
            labelScore.text = "Score final : ";
            labelTemps.text = "votre temps : ";
            btnMenu.text = "Menu Pincipal";
        }
        else
        {
            //Sc Perdu ENG
            labelTitre.text = "you lost ...";
            labelScore.text = "final score : ";
            labelTemps.text = "your time : ";
            btnMenu.text = "Main Menu";
        }
    }
}
