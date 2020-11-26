using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CheckPoint : MonoBehaviour
{

    Vector3 pos;
    const float taille = 10f;
    const float decaley = 10f;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {

        RaycastHit r;

        pos = new Vector3(transform.position.x, transform.position.y + decaley, transform.position.z);



        Debug.DrawRay(pos, -transform.up * taille, Color.red);
        if (Physics.Raycast(pos, -transform.up * taille, out r, taille))
        {
            if (r.transform.tag == "Player")
            {
                Debug.Log("CheckPoint touche (probleme assignation position)");
                r.transform.gameObject.GetComponent<mvt>().setCheckPointPosition(r.transform.gameObject);

            }
        }
    }



}

