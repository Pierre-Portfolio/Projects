using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class boutons : MonoBehaviour {
	

	public void chgt(){
		Scene active = SceneManager.GetActiveScene ();
		if (active.name == "InterfacePrinc") {
			SceneManager.LoadScene ("Credits", LoadSceneMode.Single);
		} else {
			SceneManager.LoadScene ("InterfacePrinc", LoadSceneMode.Single);
		}
	}
}
