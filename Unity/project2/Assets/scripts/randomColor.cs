using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class randomColor : MonoBehaviour
{
    // Start is called before the first frame update
    Random r = new Random();
	Renderer rend;
    // float transparency = 0.6F;
    Color randomColour;
    void Start()
    {
    	rend = GetComponent<Renderer> ();
    	randomColour = new Color(Random.Range(0f,1f), Random.Range(0f, 1f), Random.Range(0f, 1f),0.4f);
    }

    // Update is called once per frame
    void Update()
    {
        rend.material.color = randomColour;
    }
}
