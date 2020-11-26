using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class piece : MonoBehaviour
{
    public int rotateS = 150;
    public float longueurHaut = 0.8f;
    public float framelongueur = -1f;
    RaycastHit triggerTete;
    public float rcTaille = 0.38f;
    public float rcLongueur = 0.38f;

    public enum itemType { Piece, Champi, Etoile };

    public itemType type = itemType.Piece;

    // Use this for initialization
    void Start()
    {
        if (type == itemType.Piece)
        {
            transform.Rotate(new Vector3(90, 0, 0));
        }
        if (type == itemType.Champi)
        {
            transform.Rotate(new Vector3(90, 5, 0));
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (type == itemType.Piece)
        {
            transform.Rotate(new Vector3(0, 0, Time.deltaTime * rotateS));
        }
    }

    private void FixedUpdate()
    {



        //+ new Vector3(rcLongueur, rcTaille, framelongueur)

        if (this.gameObject.tag.Equals("Champi"))
        {
            ExtDebug.DrawBoxCastOnHit(transform.position + new Vector3(rcLongueur, rcTaille +0.5f, framelongueur), new Vector3(longueurHaut, longueurHaut, longueurHaut) / 2, Quaternion.identity, transform.up, 1.0f, Color.red);
            if (Physics.BoxCast(transform.position + new Vector3(rcLongueur, rcTaille+0.5f, framelongueur), new Vector3(longueurHaut, longueurHaut, longueurHaut), transform.up, out triggerTete, Quaternion.identity, 1))
            {

                if (triggerTete.transform.tag.Equals("Player"))
                {
                    if (this.gameObject.tag.Equals("Champi"))
                    {
                        triggerTete.transform.GetComponent<Questionb>().MarioDevienGrand(true);
                    }

                    Destroy(this.gameObject);
                }
            }
        }

            if (this.gameObject.tag.Equals("piece"))
            {
                ExtDebug.DrawBoxCastOnHit(transform.position + new Vector3(0, 1, 0), new Vector3(longueurHaut, longueurHaut, longueurHaut) / 2, Quaternion.identity, transform.forward, 1.0f, Color.red);
                if (Physics.BoxCast(transform.position + new Vector3(0, 1, 0), new Vector3(longueurHaut, longueurHaut, longueurHaut), transform.forward, out triggerTete, Quaternion.identity, 1))
                {
                    if (triggerTete.transform.tag.Equals("Player"))
                    {
                        if (Global.isMulti)
                        {

                            if (triggerTete.transform.gameObject.GetComponent<mvt>().getIsMine())
                            {
                                Global.score++;
                                Debug.Log("Il s'agit d'une piece");
                            }

                        }
                        else
                        {
                            Global.score++;
                            Debug.Log("Il s'agit d'une piece2");
                        }
                        Destroy(this.gameObject);
                    }
                }
            }


            

        }
    }


