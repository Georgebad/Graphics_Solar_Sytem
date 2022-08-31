using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class textureOnOff : MonoBehaviour
{
	public Material sphColor;
	public Material texture;
	public GameObject sph;
	public int code =0;
	// Texture2D myTexture;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(Input.GetKeyDown("t") & code == 0)
        {
        	sph.GetComponent<MeshRenderer> ().material = texture;
        	code +=1;
        }
        else if(Input.GetKeyDown("t") & code == 1)
        {
        	sph.GetComponent<MeshRenderer> ().material = sphColor;
        	code-=1;
        }
    }
}
