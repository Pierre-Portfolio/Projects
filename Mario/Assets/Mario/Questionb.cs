using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Questionb : MonoBehaviour
{

    public float rcTailleHaut = 0.38f;
    public float rcTailleDirection = 0.3f;
    public float rcTailleBas = 0.4f;
    public float longueurHaut = 1.0f;

    RaycastHit triggerTete;

    public bool toucheSol = true;

    public bool marioGrand = false;
    public Rigidbody piece;
    public Transform test;

    private void Start() {

        




    }



    private void FixedUpdate()
    {
        RaycastHit hit;
        RaycastHit hitAv;
        RaycastHit hitAr;
        RaycastHit hitB;

        Debug.DrawRay(transform.position, transform.up * rcTailleHaut, Color.red);
        Debug.DrawRay(transform.position, -transform.up * rcTailleBas, Color.yellow);
        Debug.DrawRay(transform.position, transform.right * rcTailleDirection, Color.green);
        Debug.DrawRay(transform.position, -transform.right * rcTailleDirection, Color.blue);

        if (Physics.Raycast(transform.position, transform.up, out hit, rcTailleHaut))
        {
            if (hit.transform.name.Equals("box"))
            {
                Destroy(hit.transform.gameObject);

            }
        }

        toucheSol = GetComponent<CharacterController>().isGrounded;

        if (Physics.Raycast(transform.position, -transform.up, out hit, rcTailleBas))// /0.5
        {

            if (hit.transform.tag.Equals("Goomba")) {

                Debug.Log("le goomba est mort");
            }
            /*
            if (hit.transform.tag.Equals("Sol"))
            {

                toucheSol = true;

            }
            else
            {

                toucheSol = false;
            }
            */

        }

        ExtDebug.DrawBoxCastOnHit(transform.position + new Vector3(0f, rcTailleHaut, 0f), new Vector3(longueurHaut, longueurHaut, longueurHaut) / 2, Quaternion.identity, transform.up, 1.0f, Color.red);
        if (Physics.BoxCast(transform.position + new Vector3(0f, rcTailleHaut, 0f), new Vector3(longueurHaut, longueurHaut, longueurHaut), transform.up, out triggerTete, Quaternion.identity, 1))
        {
            if (triggerTete.transform.tag.Equals("MysteryBlock"))
            {
                triggerTete.transform.GetComponent<MysteryBoxScript>().touche();
            }

            if (triggerTete.transform.tag.Equals("Brique"))
            {
                if (marioGrand)
                {
                    Destroy(triggerTete.transform.gameObject);
                    Global.score++;
                }
            }
        }
    }

    public void MarioDevienGrand(bool onsaispas)
    {
        if (onsaispas)
        {
            marioGrand = true;
            transform.localScale = new Vector3(0.2f, 0.2f, 0.2f);
        }
        else
        {
            marioGrand = false;
            transform.localScale = new Vector3(0.1f, 0.1f, 0.1f);
        }
        Debug.Log("On rentre bien dans la fonction");
    }





}