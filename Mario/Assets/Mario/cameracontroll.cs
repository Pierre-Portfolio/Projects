using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cameracontroll : MonoBehaviour {
		
	public GameObject Character;

	Vector3 cam;
	// Use this for initialization
	void Start () {
		cam = transform.position - Character.transform.position;
	}
	
	// Update is called once per frame
	void LateUpdate () {
		transform.position = Character.transform.position + cam;
	}
}
