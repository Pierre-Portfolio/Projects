using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class timerScript : MonoBehaviour {

	int time;
    int timeStop;
    int timeDebPause;
    int timeFin;
    int timePause;
	public Text label;
	public float timerInterval = 5f;
	float tick;
    public GameObject panelPause;

	void Start () {
		time = (int)Time.timeSinceLevelLoad;
        timeDebPause = PlayerPrefs.GetInt("timeDeb");
        timeFin = PlayerPrefs.GetInt("timeFin");
        timePause = PlayerPrefs.GetInt("timePause");
        tick = timerInterval;
        Debug.Log(tick);
    }

	void Update () {

        if(!panelPause.GetActive())
        {
            label.text = string.Format("{0:0}:{1:00}",Mathf.Floor(time/60),time%60);
						Global.temps = label.text;
            time = (int)Time.timeSinceLevelLoad - timePause;
        }
        else
        {
            timeDebPause = time;
            timeFin = (int)Time.timeSinceLevelLoad;

            timePause = timeFin - timeDebPause;
            Debug.Log("deb :" + timeDebPause + "  fin : " + timeFin+"  Pause : "+timePause);
        }
    }

	void timerExecute(){
		Debug.Log ("Timer");
	}
}
