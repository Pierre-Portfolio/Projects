﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MouvementMap : MonoBehaviour {

	public GameObject WorldMap;
	public GameObject Mario;

	// Use this for initialization
	void Start () {
		WorldMap.transform.position = new Vector3(WorldMap.transform.position.x-Mario.transform.position.x, 0.11f,0f);
	}
	
	// Update is called once per frame
	void Update () {
        WorldMap.transform.position = new Vector3(WorldMap.transform.position.x -Mario.transform.position.x, 0.11f, 0f);
	}









}