using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PlayerScript : MonoBehaviour {


    public bool devTesting = false;

    public float playerSpeed = 4f;

    private Animator anim;


    private bool isWatchingRight = true;

    private Vector3 selfPos;


    //public Joystick joyG;
    public FixedJoystick joyD;

    public string nom = "test";

    public PhotonView photonView;

    private GameObject sceneCam;

    public GameObject plCom;

    private void Awake() {

        anim = GetComponent<Animator>();

        print(photonView.isMine);

        if (!devTesting && photonView.isMine)
        {
            sceneCam = GameObject.Find("Main Camera");
            print("dans le awake");
            //sceneCam.SetActive(false);// A FAIRE GAFFE
            plCom.SetActive(true);
        }
    }

    void Start()
    {

    }

    void FixedUpdate()
    {


        if (!devTesting)
        {
            if (photonView.isMine) { 
                Bouger();
            }
            //else
              //  smoothNetMovement();
        }
        else
            Bouger();
    }

    void Bouger() {


        Vector3 t = transform.localScale;

        joyD = FindObjectOfType<FixedJoystick>();

        Vector2 targetVelocity = new Vector2(joyD.Horizontal*10, joyD.Vertical*10);
        Debug.Log("lucas");


        if (Input.GetMouseButtonDown(0)) {
            anim.SetBool("isAttacking", true);
        }
        else
            anim.SetBool("isAttacking", false);

        //print(anim.GetBool("isAttacking"));

        if (targetVelocity.x == -1 && transform.localScale.x > 0)//ON PEUT JUSTE FAIRE UN OU
        {
            t.x = t.x * -1;
            isWatchingRight = true;
            transform.localScale = t;
        }
        else if (targetVelocity.x == 1 && transform.localScale.x < 0)
        {
            isWatchingRight = false;
            t.x = t.x * -1;
            transform.localScale = t;
        }





        if (targetVelocity.x == 0 && targetVelocity.y == 0)
            anim.SetBool("isMoving", false);
        else
            anim.SetBool("isMoving", true);

        GetComponent<Rigidbody2D>().velocity = targetVelocity * playerSpeed;
    }

    //PAS OBLIGATOIRE SI ON UTILISE UN PHOTONVIEW TRANSFORM
    /* private void smoothNetMovement() {//Dans le personnage qui n'est pas le mien
         print("smooth");
         transform.position = Vector3.Lerp(transform.position, selfPos, Time.deltaTime * 8);

     }*/

    private void OnPhotonSerializeView(PhotonStream stream, PhotonMessageInfo info) {

        if (stream.isWriting)
        {
     

            //stream.SendNext(transform.position);

            

           /* stream.SendNext(anim.GetBool("isMoving"));
            stream.SendNext(anim.GetBool("isAttacking"));*/
        }
        else {
            //selfPos = (Vector3)stream.ReceiveNext();
           /* anim.SetBool("isMoving",(bool)stream.ReceiveNext());
            anim.SetBool("isAttacking", (bool)stream.ReceiveNext());*/

        }

        }

    }






