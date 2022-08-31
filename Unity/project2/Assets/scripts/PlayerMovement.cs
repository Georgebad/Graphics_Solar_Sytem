using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    public CharacterController controller;
    public float speed = 100f;
    // public GameObject cam;
    public GameObject sceneCube;

    // Update is called once per frame
    void Update()
    {
        float x = Input.GetAxis("Horizontal");
        float z = Input.GetAxis("Vertical");
        Vector3 move = transform.right * x + transform.forward * z; //+ transform.up * y;
        
        controller.Move(move * speed * Time.deltaTime);
        controller.transform.eulerAngles = new Vector3(controller.transform.eulerAngles.x,controller.transform.eulerAngles.y,0);
    }

    void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.tag=="SceneCube")
        {
            Debug.Log("xtypise");
            Physics.IgnoreCollision(collision.collider,GetComponent<Collider>());
        }
    }
}
