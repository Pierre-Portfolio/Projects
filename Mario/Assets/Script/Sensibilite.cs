using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Sensibilite : MonoBehaviour
{
    public Slider SlSensi;

    // Start is called before the first frame update
    void Start()
    {
        SlSensi.value = PlayerPrefs.GetFloat("sensi");
    }

    // Update is called once per frame
    void Update()
    {
        PlayerPrefs.SetFloat("sensi", SlSensi.value);
    }
}
