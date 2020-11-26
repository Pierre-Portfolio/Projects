using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class changerPerso : MonoBehaviour {
	public int cpt = 0;
	public Image active;
	public Image rectangle;
	public Sprite MarioClassique;
	public Sprite MarioBlanc;
	public Sprite MarioLuigi;
	public Sprite MarioWaluigi;
	public Sprite RectangleRouge;
	public Sprite RectangleVert;
	public Sprite RectangleBlanc;
	public Sprite RectangleViolet;
    public int nbperso;

    public InputField nameField;

    public void changeName() {

        Global.nom = nameField.text;
        Debug.Log(Global.nom);

    }

	public void changePerso(){
		cpt++;
		if (cpt > 3) {
			cpt = 0;
        }
		switch (cpt) {
		    case 0:
			    active.sprite = MarioClassique;
			    rectangle.sprite = RectangleRouge;
                break;
		    case 1:
			    active.sprite = MarioBlanc;
			    rectangle.sprite = RectangleBlanc;
                break;
		    case 2:
			    active.sprite = MarioLuigi;
			    rectangle.sprite = RectangleVert;
                break;
		    case 3:
			    active.sprite = MarioWaluigi;
			    rectangle.sprite = RectangleViolet;
                break;
		}

        Debug.Log("la couleur est :" + Global.color);

        Global.color = cpt;
        PlayerPrefs.SetInt("numPerso", cpt);
    }

    void Start()
    {
        nbperso = 0;
       //nbperso = PlayerPrefs.GetInt("numPerso");
        switch (nbperso)
        {
            case 0:
                active.sprite = MarioClassique;
                rectangle.sprite = RectangleRouge;
                break;
            case 1:
                active.sprite = MarioBlanc;
                rectangle.sprite = RectangleBlanc;
                break;
            case 2:
                active.sprite = MarioLuigi;
                rectangle.sprite = RectangleVert;
                break;
            case 3:
                active.sprite = MarioWaluigi;
                rectangle.sprite = RectangleViolet;
                break;
        }
    }
}
