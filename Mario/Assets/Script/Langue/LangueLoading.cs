using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class LangueLoading : MonoBehaviour
{
    public Text labelTitreChargement;

    // Use this for initialization
    void Start()
    {
        if (PlayerPrefs.GetInt("lang") == 0)
        {
            //Sc Chargement FR
            labelTitreChargement.text = "Chargement . . .";
        }
        else
        {
            //Sc Chargement ENG
            labelTitreChargement.text = "Loading . . .";
        }
    }
}
