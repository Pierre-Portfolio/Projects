using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using Hashtable = ExitGames.Client.Photon.Hashtable;
//L'animation peut buguer suite à une différence entre temps de saut et temps d'animation de saut
public class mvt : MonoBehaviour
{



    public string nom = "unassigned";

    Rigidbody rb;
    public float speed = 8;
    public float gravityScale;
    public float js = 6;
    bool saut = false;

    private Animator anim;

    private CharacterController control;
    private Vector3 direction;

    private bool isAvance = true;
    private bool onJump = false;

    public Questionb qb;

    public PhotonView photonView;

    private GameObject cam;

    private bool isMine = false;

    public Joystick joystick;
    public Joybutton BtnSauter;

    public Joystick joystickG;
    public Joybutton BtnSauterG;

    public GameObject textNom;

    public int couleur;

    public Vector3 lastCheckPointPosition;

    private bool isInvincible = false;
    public float tempsInvincible = 2f;

    public GameObject lieuSpawn;

    public float gravityScaleF = 1.0f;




    //Est recu des que quelqu'un se connecte
    //Cela signifie que l'on ne connait pas si le joueur est deja connecte
    [PunRPC]
    void SetAll(string tempString, int number)
    {

        setName(tempString);



        Debug.Log(tempString + " " + number);
    }


    [PunRPC]
    void SetAll2(int couleur, int number)
    {

        setColors(couleur);



    }





    public void setName(string n) {



        this.nom = n;
        textNom.GetComponent<TextMesh>().text = n;

    }


    public bool getIsMine() {

        return isMine;

    }

    public void setColors(int c)
    {

        SkinnedMeshRenderer skr = transform.GetChild(1).GetComponent<SkinnedMeshRenderer>();

        if (skr == null)
        {

            print("ERREUR MAT NULL");
        }

        Material[] mats = skr.materials;

        switch (c)
        {
            case 0:
                //
                break;
            case 1:
                mats[0].color = new Color(1, 0, 0);//salopette
                //mats[1].color = new Color(1, 0, 0);//boules
                mats[2].color = new Color(1, 1, 1);//chapeau + tenue
                //mats[3].color = new Color(1, 0, 0);//Peau : NON MODIF
                //mats[4].color = new Color(1, 0, 0);//Barbe + yeux
                //mats[5].color = new Color(1, 0, 0);//Yeux exterieurs
                //mats[6].color = new Color(1, 0, 0);//Gants
                //mats[7].color = new Color(1, 0, 0);//Lampe exterieur
                //mats[8].color = new Color(1, 0, 0);//Lampe interieur
                //mats[9].color = new Color(1, 0, 0);//cheuveu
                //mats[10].color = new Color(1, 0, 0);//chaussures
                break;
            case 2:
                mats[0].color = new Color(0, 0, 0);
                mats[2].color = new Color(0, 1, 0);

                break;
            case 3:
                mats[0].color = new Color(0, 0, 0);
                mats[2].color = new Color(1, 0, 1);
                break;



        }
    }

    private void applyName() {


        GameObject[] players = GameObject.FindGameObjectsWithTag("Player");
        foreach (GameObject p in players) {

            PhotonPlayer pp = p.GetComponent<PhotonView>().owner;
            if (pp != null) {

                p.GetComponent<mvt>().setName(pp.NickName);
                int c = (int)pp.CustomProperties["couleur"];

                p.GetComponent<mvt>().setColors(c);


            }
        }

    }

    public void setCheckPointPosition(GameObject v) {

        lastCheckPointPosition = v.transform.position;
    }


    // Use this for initialization
    void Start()
    {
        //rb = GetComponent<Rigidbody>();

        //Non testé.
        lieuSpawn = GameObject.FindGameObjectWithTag("CheckPoint");


        lastCheckPointPosition = transform.position;//sert plus a rien


        control = GetComponent<CharacterController>();
        anim = GetComponent<Animator>();
        control.enabled = true;

        cam = GameObject.FindGameObjectWithTag("MainCamera");


        if (cam == null) {

            Debug.Log("ERREUR");
        }

        if (Global.isMulti)
        {

            if (photonView.isMine)
            {


                Hashtable hash = new Hashtable();
                hash.Add("couleur", Global.color);
                PhotonNetwork.player.SetCustomProperties(hash);

                PhotonNetwork.player.NickName = Global.nom;

                //Faire que si t'es deja connecte tu recois les pseudos des autres joueurs.
                photonView.RPC("SetAll", PhotonTargets.All, nom, (int)28);
                photonView.RPC("SetAll2", PhotonTargets.All, Global.color, (int)28);




                //Faire que si tu te connecte, tu recupere les pseudos des autres joueurs et les appliques.
                setColors(Global.color);
                setName(Global.nom);

                applyName();


                isMine = true;

            }

        }
        else {

            isMine = true;
            setName("");
            applyName();
            setColors(Global.color);

        }

        if (isMine) {


            joystick = GameObject.FindGameObjectWithTag("CanvasD").GetComponent<StockJoystick>().joystick;
            BtnSauter = GameObject.FindGameObjectWithTag("CanvasD").GetComponent<StockJoystick>().btnA;

            joystickG = GameObject.FindGameObjectWithTag("CanvasG").GetComponent<StockJoystick>().joystick;
            BtnSauterG = GameObject.FindGameObjectWithTag("CanvasG").GetComponent<StockJoystick>().btnA;

        }
        /*
                if (Global.isVR)
                {

                }
                else
                {
                    cameracontroll cc = cam.GetComponent<cameracontroll>();
                    cc.GetComponent<cameracontroll>().enabled = true;
                    cc.Character = this.gameObject;
                    cam.gameObject.SetActive(true);
                }

                */


    }



    private IEnumerator estInvincible() {

        isInvincible = true;

        yield return new WaitForSeconds(tempsInvincible);

        Debug.Log("mario n'est plus invincible");

        isInvincible = false;

    }


    public void finGagner() {

        SceneManager.LoadScene("Gagner");

    }

    public void finPerdu() {


        SceneManager.LoadScene("Perdu");


    }


    public void mort() {


        if (Global.isMulti) {

            Debug.Log("mario est vraiment mort");

            transform.position = lieuSpawn.transform.position;

        }
        else
        {
            SceneManager.LoadScene("Perdu");
            Debug.Log("game Over");


        }

    }

    public void degat() {

        Questionb qb = GetComponent<Questionb>();

        if (!isInvincible)
        {
            if (qb.marioGrand)
            {

                qb.MarioDevienGrand(false);

            }
            else {

                mort();

            }

            StartCoroutine(estInvincible());



        }



    }



    // Update is called once per frame
    void Update()
    {
        //float moveH = Input.GetAxis ("Vertical");

        //Vector3 mvt = new Vector3 (moveH, 0);

        if (isMine)
        {/*
            if (PlayerPrefs.GetInt("rightLeft") == 1){
                direction = new Vector3(joystick.Horizontal * speed + Input.GetAxis("Horizontal") * speed, direction.y);
            }else{
                direction = new Vector3(joystickG.Horizontal * speed + Input.GetAxis("Horizontal") * speed, direction.y);
            }
            */
            if (!Global.isGaucher)
            {
                direction = new Vector3(joystick.Horizontal * speed + Input.GetAxis("Horizontal") * speed, direction.y);
            }
            else
            {
                direction = new Vector3(joystickG.Horizontal * speed + Input.GetAxis("Horizontal") * speed, direction.y);
            }




            if (qb.toucheSol)
            {
                anim.ResetTrigger("JumpRun");

                if (BtnSauter.Pressed ||BtnSauterG.Pressed || Input.GetKeyDown(KeyCode.Space))
                {
                    anim.SetTrigger("JumpRun");
                    direction.y = js;
                }
                anim.SetBool("isJumping", false);

            }
            else
            {
                anim.SetBool("isJumping", true);

                //Debug.Log("trigger Jumping");

            }



            if (!control.isGrounded)
            {
                direction.y = direction.y + (Physics.gravity.y * gravityScaleF * Time.deltaTime);
            }

            direction.y = direction.y + (Physics.gravity.y * gravityScale * Time.deltaTime);



            control.Move(direction * Time.deltaTime);

            bool isMoving = direction.x != 0;

            isAvance = direction.x >= 0;
            if (isMoving)
            {
                if (isAvance)
                {
                    transform.rotation = Quaternion.AngleAxis(80, Vector3.up);
                }
                else
                {
                    transform.rotation = Quaternion.AngleAxis(-100, Vector3.up);
                }
            }



            anim.SetBool("isRunning", isMoving);


            //Debug.Log("courir :" + isMoving + "jumping :"+ !control.isGrounded);

            //saut = false;

            //rb.AddForce (mvt * speed);
        }
    }


    private void OnPhotonSerializeView(PhotonStream stream, PhotonMessageInfo info)
    {

        if (stream.isWriting)
        {


        }
        else
        {


        }

    }

}
