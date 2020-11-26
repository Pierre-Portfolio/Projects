using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class joyconnect : MonoBehaviour
{
    protected Joystick joystick;
    public Joystick joyG;
    public Joystick joyD;

    // Start is called before the first frame update
    void Start()
    {
        if(PlayerPrefs.GetInt("rightLeft") == 1)
        {
            joystick = joyD;
        }
        else
        {
            joystick = joyG;
        }
    }

    // Update is called once per frame
    void Update()
    {
        var rigidbody = GetComponent<Rigidbody>();
        float sensitivity = PlayerPrefs.GetFloat("sensi");
        rigidbody.velocity = new Vector3(joystick.Horizontal * sensitivity, rigidbody.velocity.y, joystick.Vertical * sensitivity);
    }
}
