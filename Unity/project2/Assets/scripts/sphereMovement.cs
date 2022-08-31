using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class sphereMovement : MonoBehaviour
{
	public GameObject sphere;
	public float speed = 10.0f;
	public Rigidbody rb;
	// public Vector3 position = this.transform.position;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    public int xx = 50;
    public int yy = 50;
    public int zz = 50;
    void Update()
    {
    	Vector3 position = this.transform.position;
        if (Input.GetKey(KeyCode.LeftArrow) && position.x>15f)
        {
            position.x-=0.15f;
            this.transform.position = position;
        }
        if (Input.GetKey(KeyCode.RightArrow) && position.x < 85f)
        {
            position.x+=0.15f;
            this.transform.position = position;
        }
        if (Input.GetKey(KeyCode.UpArrow) && position.y < 85f)
        {
            position.y += 0.15f;
            this.transform.position = position;
        }
        if (Input.GetKey(KeyCode.DownArrow) && position.y > 15f)
        {
            position.y -= 0.15f;
            this.transform.position = position;
        }
        if (Input.GetKey(KeyCode.Period) && position.z >15f)
        {
            position.z -= 0.15f;
            this.transform.position = position;
        }
        if (Input.GetKey(KeyCode.Comma) && position.z < 85f)
        {
            position.z += 0.15f;
            this.transform.position = position;
        }
    }
}
