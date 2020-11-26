using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class LangueConnection : MonoBehaviour
{
    //texte compris dans section 1
    public Text titreConnexion;
    //texte compris dans section 1
    public Text btnRejoindre;
    public Text btncreer;
    public Text inputfield1;
    public Text inputfield2;
    public Text labelconnecter;
    //texte compris dans section 1
    public Text titreCoPerdu;

    // Use this for initialization
    void Start()
    {
        if (PlayerPrefs.GetInt("lang") == 0)
        {
            //Sc Multi FR
            //section 1
            titreConnexion.text = "Patientez Connexion a Photon . . .";
                //Ssection 2
            btnRejoindre.text = "Rejoindre";
            btncreer.text = "Creer";
            inputfield1.text = inputfield2.text = "Entrer texte . . .";
            labelconnecter.text = "Connecte";
                //section3
            titreCoPerdu.text = "Connexion Perdu";
        }
        else
        {
            //Sc Multi ENG
                //section 1
            titreConnexion.text = "Waiting Connection to Photon . . .";
            //section2
            btnRejoindre.text = "Join";
            btncreer.text = "Create";
            inputfield1.text = inputfield2.text = "Enter text . . .";
            labelconnecter.text = "Connected";
            //section3
            titreCoPerdu.text = "Connection Lost";
        }
    }
}
