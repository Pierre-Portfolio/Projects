using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PreventFall : MonoBehaviour
{
    RaycastHit rc;
    public float taille = 400f;
    public float decale = 5f;



    //Attention qu'il soit parfaitement sur la ligne de deplacement de Mario

    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {

        Vector3 newPos = new Vector3(transform.position.x, transform.position.y, transform.position.z);



        Debug.DrawRay(newPos, transform.right * taille, Color.red);//etrange car devrait etre tranform.up
        if (Physics.Raycast(newPos, transform.right * taille, out rc, taille))
        {
            if (rc.transform.tag == "Player")
            {

                rc.transform.GetComponent<mvt>().mort();

            }
        }


    }
}
