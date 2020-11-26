using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MysteryBoxScript : MonoBehaviour
{

    public enum itemSpawn { Piece, Champi, Etoile };
    public itemSpawn type = itemSpawn.Piece;

    private bool actif = true;

    public GameObject piece;
    public GameObject Hongo;
    public Material newMat;

    // Start is called before the first frame update
    void Start()
    {


    }

    public void touche() {


        if (actif) {
            actif = false;

            if (type == itemSpawn.Piece) {
                GameObject instancepiece;
                Vector3 posChange = new Vector3(0, 1.2f, 0);
                Vector3 pos = transform.position + posChange;
                instancepiece = Instantiate(piece, pos, Quaternion.identity);
                instancepiece.transform.parent = this.transform;
                GetComponent<Renderer>().material = newMat;

            }

            if (type == itemSpawn.Champi) {
              GameObject instanceHongo;
              Vector3 posChange = new Vector3(0.2f, 1.1f, 0);
              Vector3 pos = transform.position + posChange;
              instanceHongo = Instantiate(Hongo, pos, Hongo.transform.rotation);
                instanceHongo.transform.parent = this.transform;
              GetComponent<Renderer>().material = newMat;
            }


        }

    }

    // Update is called once per frame
    void Update()
    {

    }
}
