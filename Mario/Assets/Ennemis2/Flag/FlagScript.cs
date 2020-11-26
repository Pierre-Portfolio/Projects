using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FlagScript : MonoBehaviour {

    // Use this for initialization
    private Animator anim;
	RaycastHit rcDrapeau ;
	public float taille=10f;
    public float decale = 5f;

    public GameObject bas;

    private bool fin = false;
    public float tempsAvFin = 2f;

    private GameObject m;

	void Start () {

        anim = GetComponent<Animator>();

	}

    IEnumerator timerAvFin()
    {


        yield return new WaitForSeconds(tempsAvFin);


        //m.GetComponent<mvt>().finGagner();

        foreach (GameObject g in GameObject.FindGameObjectsWithTag("Player"))
        {

            if (g.Equals(m))
            {
                g.GetComponent<mvt>().finGagner();
            }
            else
            {
                g.GetComponent<mvt>().finPerdu();
            }



        }
    }

	// Update is called once per frame
	void Update () {



       Vector3 newPos =new Vector3 (transform.position.x,transform.position.y - decale,transform.position.z);


        if (!fin)
        {
            Debug.DrawRay(newPos, transform.forward * taille, Color.red);//etrange car devrait etre tranform.up
            if (Physics.Raycast(newPos, transform.forward * taille, out rcDrapeau, taille))
            {
                if (rcDrapeau.transform.tag == "Player")
                {
                    anim.SetBool("isTaken", true);
                    fin = true;
                    m = rcDrapeau.transform.gameObject;
                    StartCoroutine(timerAvFin());
                    print("fin du jeu, le drapeau a ete touche.");

                }
            }
        }
        
        
	}
}
