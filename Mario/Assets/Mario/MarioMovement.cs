using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MarioMovement : MonoBehaviour {


    public float speed = 6.0f;
    public float jumpSpeed = 20.0f;
    public float gravity = 20.0f;

    private Animator anim;
    private Rigidbody rigidbody;

    private Vector3 moveDirection = Vector3.zero;
    private CharacterController controller;

    private Vector3 lastCheckPointPosition;

    void Start()
    {

        this.transform.position = lastCheckPointPosition;

        rigidbody = GetComponent<Rigidbody>();
        anim = GetComponent<Animator>();
        controller = GetComponent<CharacterController>();


        // let the gameObject fall down
        //gameObject.transform.position = new Vector3(0, 5, 0);
    }

    public void setCheckPoint(GameObject g) {

        lastCheckPointPosition = g.transform.position;

    }


    public void damage(int v) {



        Debug.Log("mario se prend" + v + " degats");

        this.transform.position = lastCheckPointPosition;
    }


    void Update()
    {
        //controller.enabled = true;
        //if (controller.isGrounded)
        //{
            moveDirection = new Vector3(Input.GetAxis("Horizontal"), 0.0f, Input.GetAxis("Vertical"));

            //moveDirection = transform.TransformDirection(moveDirection);
            moveDirection = moveDirection * speed/100.0f;
        transform.position = transform.position + moveDirection;

        bool isMoving = (Input.GetAxis("Horizontal") != 0 || Input.GetAxis("Vertical") != 0);

        anim.SetBool("isRunning", isMoving);
        //Debug.Log("val bool" + anim.GetBool("isRunning"));

        if (isMoving)
        {
            float myAngle = Mathf.Atan2(Input.GetAxis("Horizontal"), Input.GetAxis("Vertical")) * Mathf.Rad2Deg;
            transform.rotation = Quaternion.AngleAxis(myAngle, Vector3.up);
        }
        //float bodyRotation = myAngle + camera.transform.eulerAngles.y;


        if (Input.GetKeyDown(KeyCode.Space))
        {
            rigidbody.velocity += jumpSpeed * Vector3.up;
        }

        /*if (Input.GetButton("Jump"))
                {
                    moveDirection.y = jumpSpeed;
                }
       }*/

        // Apply gravity
        //moveDirection.y = moveDirection.y - (gravity * Time.deltaTime);

        // Move the controller
        //controller.Move(moveDirection * Time.deltaTime);
    }
}
