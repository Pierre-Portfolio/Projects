using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Audio;

public class LangueCredit : MonoBehaviour
{
    public Text btnGpProg;
    public Text btnGpCreation;
    public Text btnGpInterface;
    public Text btnGpAnimation;
    public Text btnGpGestion;

    // Use this for initialization
    void Start()
    {
        if (PlayerPrefs.GetInt("lang") == 0)
        {
            //Sc Credit FR
            btnGpAnimation.text = "Equipe Animation";
            btnGpCreation.text = "Equipe Creation ";
            btnGpGestion.text = "Equipe\nGestion / RA";
            btnGpInterface.text = "Equipe Interface";
            btnGpProg.text = "Equipe Programmation";
        }
        else
        {
            //Sc Credit ENG
            btnGpAnimation.text = "Animation Team";
            btnGpCreation.text = "Creative Team";
            btnGpGestion.text = "Management Team / AR";
            btnGpInterface.text = "Interface Team";
            btnGpProg.text = "Programming\nTeam";
        }
    }
    void Update()
    {
        if (PlayerPrefs.GetInt("lang") == 0)
        {
            //Sc Credit FR
            btnGpAnimation.text = "Equipe Animation";
            btnGpCreation.text = "Equipe Creation";
            btnGpGestion.text = "Equipe\nGestion / RA";
            btnGpInterface.text = "Equipe Interface";
            btnGpProg.text = "Equipe Programmation";
        }
        else
        {
            //Sc Credit ENG
            btnGpAnimation.text = "Animation Team";
            btnGpCreation.text = "Creative Team";
            btnGpGestion.text = "Management Team / AR";
            btnGpInterface.text = "Interface Team";
            btnGpProg.text = "Programming\nTeam";
        }
    }
}
