using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class lan2 : MonoBehaviour {

    public Text labelTitreGagner;
    public Text labelTitrePerdu;
    public Text labelTemps;
    public Text labelScore;

    public Text labelTitrePause;
    public Text btnContinuer;
    public Text btnParametre;
    public Text btnMenuPrincipal;

    // Use this for initialization
    void Start () {
		if (PlayerPrefs.GetInt ("lang") == 0) {
            //Sc Gagner - Perdu
            labelTitreGagner.text = "Tu as gagner";
            labelTitrePerdu.text = "Tu as perdu";
            labelScore.text = "Score final";
            labelTemps.text = "votre temps";
            //Sc Pause
            labelTitrePause.text = "Pause";
            btnContinuer.text = "Continuer";
            btnParametre.text = "Parametre";
            btnMenuPrincipal.text = "Menu Principal";
            
            
        } else {
            labelTitreGagner.text = "you won";
            labelTitrePerdu.text = "You lost";
            labelScore.text = "final score";
            labelTemps.text = "your time";
            //Sc Pause
            labelTitrePause.text = "Paused";
            btnContinuer.text = "Continue";
            btnParametre.text = "Setting";
            btnMenuPrincipal.text = "Main Menu";
        }
	}
	void Update(){
		if (PlayerPrefs.GetInt ("lang") == 0) {
            labelTitreGagner.text = "Tu as gagner";
            labelTitrePerdu.text = "Tu as perdu";
            labelScore.text = "Score final";
            labelTemps.text = "votre temps";
            //Sc Pause
            labelTitrePause.text = "Pause";
            btnContinuer.text = "Continuer";
            btnParametre.text = "Parametre";
            btnMenuPrincipal.text = "Menu Principal";
        } else {
            labelTitreGagner.text = "you won";
            labelTitrePerdu.text = "You lost";
            labelScore.text = "final score";
            labelTemps.text = "your time";
            //Sc Pause
            labelTitrePause.text = "Paused";
            btnContinuer.text = "Continue";
            btnParametre.text = "Setting";
            btnMenuPrincipal.text = "Main Menu";
        }
	}
}
