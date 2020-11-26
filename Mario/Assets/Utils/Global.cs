using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Global : MonoBehaviour {

    public static int score = 0;
    public static bool isVR = true;
    public static bool isMulti = false;
    public static bool isGaucher = PlayerPrefs.GetInt("rightLeft") == 0;
    public static string nom = "unassigned";
    public static int color = PlayerPrefs.GetInt("numPerso");
    public static string temps = "0:00";
    public static bool musiqueSTOP = false;
}
