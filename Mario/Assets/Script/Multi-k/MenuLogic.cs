using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MenuLogic : MonoBehaviour {

    //INUTILE A SUPPRIMER PLUS TARD
    public void disableMenuUI() {
        PhotonNetwork.LoadLevel("Jeu");
    }
}
