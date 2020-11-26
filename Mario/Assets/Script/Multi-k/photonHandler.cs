using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;

public class photonHandler : MonoBehaviour {

    public PhotonButtons photonB;
    public GameObject mainPlayer;

    private void Awake() {
        DontDestroyOnLoad(this.transform);
        SceneManager.sceneLoaded += OnSceneFinishedLoading;//ATSTER
    }

    public void createNewRoom() {

        PhotonNetwork.CreateRoom(photonB.createRoomInput.text, new RoomOptions() { MaxPlayers = 4 }, null);
    }


    public void joinOrCreateRoom() {

        RoomOptions roomOptions = new RoomOptions();
        roomOptions.MaxPlayers = 4;
        PhotonNetwork.JoinOrCreateRoom(photonB.joinRoomInput.text, roomOptions, TypedLobby.Default);
    }

    public void moveScene() {
        photonB = null;//FAIRE GAFFE MODIFIE APRES

        if (Global.isVR == true)
        {
            PlayerPrefs.SetInt("activeAr", 1);
            PhotonNetwork.LoadLevel("MarioMapAR");
        }
        else
        {
            PlayerPrefs.SetInt("activeAr", 0);
            PhotonNetwork.LoadLevel("MarioMapNoAr");
        }

    }

    private void OnJoinedRoom()
    {
        Debug.Log("We are connected to the room");
        moveScene();
        //PhotonNetwork.LoadLevel("Jeu");


    }



    private void OnSceneFinishedLoading(Scene scene, LoadSceneMode mode)
    {
    }
    /*
    if (scene.name == "MarioMap") {
        spawnPlayer();
    }
    if (scene.name == "MarioMapNoAr")
    {
        spawnPlayer();
    }

}

private void spawnPlayer() {
    Debug.Log("Coucou "+mainPlayer.name);
    print(mainPlayer.name);
    PhotonNetwork.Instantiate(mainPlayer.name, mainPlayer.transform.position, mainPlayer.transform.rotation , 0);

}
*/

}
