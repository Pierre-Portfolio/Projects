using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GoombaMove : MonoBehaviour {


	public float rcTaille = 0.35f;
    // starting value for the Lerp
	public float taille =0.2f;

	private Animator anim;
    public float rcGoomba = 1;
    public float rMort = 1;

    public float longueurHaut = 0.18f;
	public float longueurHaut2 = 0.18f;
    public float longueurCote = 0.2f;
	public float adjust = 1.2f; // pour adjuster la hauteur de la boxcast
    public float adjust2 = 0.4f;
    Vector3 origin;
    public float distance = 1f;
    public float speed = 0.2f;
    bool movingRight = true;
    public bool test = false;

    private bool isMort = false;

    void Start(){

        origin = transform.position;

		anim = GetComponent<Animator> ();
     //   origin = this.transform.position;
	
	}





    void FixedUpdate()
    {


        if (!isMort)
        {

            RaycastHit rcMort;
            RaycastHit haut;

            Vector3 pos = transform.position;

            if (test) {

                Debug.Log("movingRight:"+movingRight);
            }

            if (movingRight)
            {
                if (pos.x > origin.x + distance)
                {
                    transform.Rotate(0, 180, 0, Space.World);
                    movingRight = false;
                }
                else
                {
                    pos.x += Time.deltaTime * speed;
                    transform.position = pos;
                }
            }
            else
            {
                if (pos.x < origin.x - distance)
                {
                    transform.Rotate(0, 180, 0, Space.World);
                    movingRight = true;
                }
                else
                {
                    pos.x -= Time.deltaTime * speed;
                    transform.position = pos;
                }
            }

            Vector3 newPos = new Vector3(pos.x, pos.y + adjust, pos.z);
            Vector3 newPos2 = new Vector3(pos.x, pos.y + adjust2, pos.z);

            //Faire que ca desactive la mort de goomba quand Mario touche et meurt car il peut traverser et le tuer.

            ExtDebug.DrawBoxCastOnHit(newPos, new Vector3(longueurHaut, longueurHaut, longueurHaut), Quaternion.identity, transform.up * -1f, rcGoomba, Color.red);
            if (Physics.BoxCast(newPos, new Vector3(longueurHaut, longueurHaut, longueurHaut), transform.up * -1f, out haut, Quaternion.identity, rcGoomba))
            {

                if (haut.transform.tag == "Player")
                {
                    Debug.Log("mario se prend des degats dans GoombaMove");

                    haut.transform.GetComponent<mvt>().degat();
                    //Destroy(haut.transform.gameObject);
                    //Destroy (derriere.transform.gameObject);

                }
            }

            
            ExtDebug.DrawBoxCastOnHit(transform.position + new Vector3(0f, 0.2f, 0f), new Vector3(longueurHaut2, longueurHaut2, longueurHaut2), Quaternion.identity, transform.up, rMort, Color.blue);
            if (Physics.BoxCast(transform.position + new Vector3(0f, 0.2f, 0f), new Vector3(longueurHaut2, longueurHaut2, longueurHaut2), transform.up, out rcMort, Quaternion.identity, rMort))
            {
                if (rcMort.transform.tag == "Player")
                {
                    isMort = true;
                    Debug.Log("Le Goomba Meurt");
                    anim.SetBool("isMort", true);
                    StartCoroutine(attenteFinAnimation());
                    
                    //Destroy(this.gameObject);
                    //Destroy (derriere.transform.gameObject);

                }
            }
        }


    }


    IEnumerator attenteFinAnimation() {

        yield return new WaitForSeconds(1);

        Destroy(this.gameObject);


    }

    }