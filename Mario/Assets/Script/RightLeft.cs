using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
//using UnityEngine.UI;

public class RightLeft : MonoBehaviour
{
    public Canvas joyD;
    public Canvas joyG;
    
    // Start is called before the first frame update
    void Start()
    {
          if(PlayerPrefs.GetInt("rightLeft") == 1)
        {
            joyD.enabled = true;
            joyG.enabled = false;
            Debug.Log("Droitier");
        }
        else
        {
            joyG.enabled = true;
            joyD.enabled = false;
            Debug.Log("Gaucher");
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
