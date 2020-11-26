using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ChangeButton : MonoBehaviour
{
    public void btnChangeSc()
    {
        Scene scAct = SceneManager.GetActiveScene();
        if (scAct.name.Equals("ScenePrincipale"))
        {
            SceneManager.LoadScene("ScSetting");
        }
        else
        {
            SceneManager.LoadScene("ScenePrincipale");
        }
    }
}
