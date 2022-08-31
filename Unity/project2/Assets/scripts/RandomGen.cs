using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RandomGen : MonoBehaviour 
{
    public GameObject[] objects = new GameObject[3];
    public int rand_obj;
    public float objSpeed = 2000.0f;
    // This script will simply instantiate the Prefab when the game starts.
    void Start()
    {
        transform.position = new Vector3(0.2f,0.2f, 0.2f);
    }
    // used in each frame
    void Update()
    {

        if(Input.GetKeyDown("b"))
        {
            objSpeed += 10f;
        }

        objects[0].SetActive(true);
        objects[1].SetActive(true);
        objects[2].SetActive(true);
        if(Input.GetKeyDown("space"))
        {
            rand_obj = Random.Range(0,3);//picking the object to instantiate
            
            float x = Random.Range(0.1f,0.9f);//*********************************
            float y = Random.Range(0.1f,0.9f);// creating the vector of direction
            float z = Random.Range(0.1f,0.9f);//*********************************

            float scaleSize = Random.Range(1f,10f);// random value for scaling the object
            Vector3 start = new Vector3(0f,0f, 0f);// starting position
            Vector3 forceVector = new Vector3(x,y,z);// where to apply the force
            if(rand_obj==1)
            {
                GameObject newObject = Instantiate(objects[rand_obj],start,Quaternion.identity) as GameObject;
                newObject.transform.localScale = new Vector3(scaleSize, (scaleSize/2), scaleSize);
                newObject.GetComponent<Rigidbody>().AddForce(forceVector*objSpeed, ForceMode.Acceleration);
            }
            else
            {
                GameObject newObject = Instantiate(objects[rand_obj],start,Quaternion.identity) as GameObject;
                newObject.transform.localScale = new Vector3(scaleSize, scaleSize, scaleSize);
                newObject.GetComponent<Rigidbody>().AddForce(forceVector*objSpeed, ForceMode.Acceleration);
            }
        }
    }

}
// Force            Add a continuous force to the rigidbody, using its mass.
// Acceleration     Add a continuous acceleration to the rigidbody, ignoring its mass.
// Impulse          Add an instant force impulse to the rigidbody, using its mass.
// VelocityChange   Add an instant velocity change to the rigidbody, ignoring its mass.