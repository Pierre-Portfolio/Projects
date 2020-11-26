using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Mouvement_du_monde : MonoBehaviour
{

    public CharacterController control;

    public GameObject Game;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        Debug.Log(control.transform.position);
        //Game.transform.position(new Vector3(- control.transform.position,0,0));
    }
}
