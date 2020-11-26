using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class LangueMenu : MonoBehaviour
{
    public Text btnJouer;
    public Text btnChanger;
    public Text TextInputPseudo;

    public InputField pseudo;
    public Image active;
    public Image rectangle;

    // Use this for initialization
    void Start()
    {
        //Sauvegarde login
        pseudo.text = PlayerPrefs.GetString("psedeau");
        Debug.Log("on start : "+pseudo.text);

        //Changement de langue
        if (PlayerPrefs.GetInt("lang") == 0)
        {
            //Sc Principal(Menu) FR
            btnChanger.text = "Changer";
            btnJouer.text = "Jouer";
            TextInputPseudo.text = "Pseudo";
        }
        else
        {
            //Sc Principal(Menu) ENG
            btnChanger.text = "Change";
            btnJouer.text = "Play";
            TextInputPseudo.text = "Username";
        }
    }
    void Update()
    {
        PlayerPrefs.SetString("psedeau", pseudo.text);
        pseudo.text = PlayerPrefs.GetString("psedeau");
        PlayerPrefs.SetInt("perso", 0);
        int perso = 0;
        switch (perso)
        {
            case 0: PlayerPrefs.SetInt("perso", 0);
                break;
        }
    }
}
