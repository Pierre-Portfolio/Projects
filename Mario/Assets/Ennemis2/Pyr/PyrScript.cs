using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PyrScript : MonoBehaviour {

    Animator animator;
	public float tempavantmort = 1.0F;
	public float rcTaille = 0.35f;
	// starting value for the Lerp
	public float taille =0.5f; // adjuster la hauteur du boxcast
	private bool marioInEnnemy = false;
	private Animator anim;
	public float rcGoomba = 1;
	public float adjustextension= 0.25f;
	public float longueurHaut = 0.5f;
	public float longueurCote = 0.2f;

	Vector3 origin;
	public float distance;
	public float speed = 0.2f;


	// Use this for initialization
	void Start () {

        //animator = GetComponent<Animator>();
		//origin = this.transform.position;

	}

	// Update is called once per frame
	void Update () {

		RaycastHit haut;
		float rcGoomba = 0.35f;
		//this.animator.Play("Agrandir");
		//AnimatorStateInfo state = anim.GetCurrentAnimatorStateInfo(0);
		//Debug.Log(this.animator.GetCurrentAnimatorStateInfo(0).ToString());
		//Debug.Log (this.animator.GetCurrentAnimatorStateInfo(0).IsName("Agrandir"));
	/*	if (this.animator.GetCurrentAnimatorStateInfo(0).IsName("Agrandir")  )
        {
            Debug.Log("est en train de grandir");
			taille = 1f;

        }
*/
		/*
		Debug.DrawRay ( transform.position + new Vector3(0f,taille,0f),transform.forward , Color.red);
		if (Physics.Raycast (transform.position+ new Vector3(0f,taille,0f), transform.forward, out devant, rcGoomba)) {
			//Debug.Log("ici" );
			if (devant.transform.tag=="Player") {

			//	Destroy (devant.transform.gameObject);

			}
		}
		Debug.DrawRay (transform.position + new Vector3(0f,taille,0f), -transform.forward, Color.red);
		if (Physics.Raycast (transform.position+ new Vector3(0f,taille,0f), -transform.forward, out derriere, rcGoomba)) {

			if (derriere.transform.tag=="Player") {

			//	Destroy (derriere.transform.gameObject);

			}
		}*/
		Vector3 newPos = new Vector3(transform.position.x, transform.localScale.y, transform.position.z);
		newPos.y = newPos.y * adjustextension ;
		newPos = newPos + new Vector3(0f,transform.position.y,0f); // adjustement de la boxcast
		ExtDebug.DrawBoxCastOnHit(newPos , new Vector3(longueurHaut, longueurHaut, longueurHaut), Quaternion.identity, transform.up, rcGoomba, Color.red);
		if (Physics.BoxCast(newPos, new Vector3(longueurHaut, longueurHaut, longueurHaut), transform.up, out haut, Quaternion.identity, rcGoomba)){
				Debug.Log("touche haut");
				if (haut.transform.tag == "Player")
				{
          haut.transform.GetComponent<mvt>().degat();
					Debug.Log("Le Mario Meurt");
					//Destroy(haut.transform.gameObject);
					//Destroy (derriere.transform.gameObject);

				}
			}
    }



}
