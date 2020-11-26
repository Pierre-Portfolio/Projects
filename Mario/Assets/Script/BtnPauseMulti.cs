using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class BtnPauseMulti : MonoBehaviour
{
    public GameObject PanelPause;
    public string nom;

    private void Update()
    {
        Scene scActive = SceneManager.GetActiveScene();
        name = scActive.name;

        if (Input.GetKeyDown(KeyCode.Escape))
        {
            Application.Quit();
        }
    }


    public void Pause()
    {
        PanelPause.SetActive(true);
        PlayerPrefs.SetInt("btnPActif", 1);
    }
    
    public void BtnContinue()
    {
        PanelPause.SetActive(false);
        PlayerPrefs.SetInt("btnPActif", 1);
    }
}
