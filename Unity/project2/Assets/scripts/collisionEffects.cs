using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class collisionEffects : MonoBehaviour
{
    // Start is called before the first frame update
    public AudioSource audioSRC;
    public int collisionCount=0;
    public ParticleSystem particles;
    // ParticleSystem.ColorOverLifetimeModule colorModule;
    void Start()
    {
    	audioSRC = GetComponent<AudioSource>();
        // colorModule = particles.GetComponent<ColorOverLifetimeModule>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnCollisionEnter()
    {
    	if(collisionCount>2)
    	{
    		audioSRC.Play();
            // colorModule.color = new Color(Random.Range(0f,1f), Random.Range(0f, 1f), Random.Range(0f, 1f));
            Instantiate(particles, transform.position,Quaternion.identity);
            // colorModule.color = new Color(Random.Range(0f,1f), Random.Range(0f, 1f), Random.Range(0f, 1f));
            // Destroy(particles);
    	}
    	else
    	{
    		collisionCount+=1;
    	}
    	// audioSRC.Play();
    }
}
