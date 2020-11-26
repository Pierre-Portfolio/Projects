using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Loading : MonoBehaviour
{
    public GameObject loading;
    public Slider slLoading;
    public Toggle tgAR;
    public string nom;

    private void Update()
    {

        if (tgAR != null)
        Global.isVR = tgAR.isOn;//a opti

        Scene scActive = SceneManager.GetActiveScene();
        name = scActive.name;
        
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            LoadLevel(PlayerPrefs.GetString("testSc"));
        }
    }


    public void LoadLevel(string sceneIndex)
    {
     
        if(sceneIndex == "ScSetting"|| sceneIndex == "TestJoystick")
        {
            PlayerPrefs.SetString("testSc",this.name);
        }
        StartCoroutine(LoadAsynchro(sceneIndex));
    }

    IEnumerator LoadAsynchro(string sceneInd)
    {
        AsyncOperation op = SceneManager.LoadSceneAsync(sceneInd);
        

        loading.SetActive(true);

        while (!op.isDone)
        {
            float progress = Mathf.Clamp01(op.progress / .9f);

            slLoading.value = progress;

            yield return null;
        }
    }
    public void BtnChangeSettings()
    {
        
        LoadLevel(PlayerPrefs.GetString("testSc"));
    }

    public void BtnPlay()
    {
        if (tgAR.isOn == true)
        {
            PlayerPrefs.SetInt("activeAr", 1);
            Global.isVR = true;
            LoadLevel("MarioMapAR");
        }
        else
        {
            PlayerPrefs.SetInt("activeAr", 0);
            Global.isVR = false;
            LoadLevel("MarioMapNoAr");
        }
    }
}
