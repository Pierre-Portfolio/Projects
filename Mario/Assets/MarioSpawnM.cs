using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MarioSpawnM : MonoBehaviour
{

    public GameObject marioPrefab;
    public GameObject marioIn;
    public GameObject myMario;

    public GameObject cam;

    // Start is called before the first frame update
    void Start()
    {
        Debug.Log(Global.isMulti);
        if (Global.isMulti) {

            Debug.Log("NOM GLOBAL"+Global.nom);

            myMario = PhotonNetwork.Instantiate(marioPrefab.name, marioIn.transform.position, marioIn.transform.rotation, 0);
            Debug.Log(myMario);
            myMario.GetComponent<mvt>().nom = Global.nom;
            myMario.GetComponent<mvt>().couleur = Global.color;
            marioIn.SetActive(false);

            
            

            cam.GetComponent<cameracontroll>().Character = myMario;
            cam.GetComponent<cameracontroll>().gameObject.SetActive(true);
            cam.SetActive(true);

        }


    }


    private void testSyncNom() {

        GameObject[] playersInGame = GameObject.FindGameObjectsWithTag("Player");
        foreach (GameObject player in playersInGame)
        {
            Debug.Log("There is someone named: " + player.GetComponent<mvt>().nom + " in the game!");
        }

    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
