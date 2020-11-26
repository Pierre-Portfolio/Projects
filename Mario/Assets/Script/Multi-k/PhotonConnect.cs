using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PhotonConnect : MonoBehaviour {

    public string versionName = "0.1";
    public GameObject sectionView1, sectionView2, sectionView3;

    private void Start() {

        Global.isMulti = true;

    }


    private void Awake() {//Si marche pas utiliser start
        PhotonNetwork.ConnectUsingSettings(versionName);
        Debug.Log("Connecting to photon ...");

    }

    private void OnConnectedToMaster() {
        PhotonNetwork.JoinLobby(TypedLobby.Default);
        Debug.Log(" we are connected to master");
    }

    private void OnJoinedLobby() {

        sectionView1.SetActive(false);
        sectionView2.SetActive(true);



        Debug.Log("On joined Lobby");

    }

    private void OnDisconnectedFromPhoton() {

        if (sectionView1.activeSelf)
            sectionView1.SetActive(false);

        if (sectionView2.activeSelf)
            sectionView2.SetActive(false);

        sectionView3.SetActive(true);



        Debug.Log("disconnected from photon services");
    }


	
	// Update is called once per frame
	void Update () {
		
	}
}
