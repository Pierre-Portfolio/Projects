using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class gif : MonoBehaviour {

	public Texture2D[] frames;
	public int fps = 8;
	// Use this for initialization

	// Update is called once per frame
	void Update () {
		int index = (int)(Time.time * fps) % frames.Length;
		GetComponent<RawImage> ().texture = frames [index];
	}
}