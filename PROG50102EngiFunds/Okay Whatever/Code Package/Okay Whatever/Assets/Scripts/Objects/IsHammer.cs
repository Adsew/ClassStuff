using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsHammer : MonoBehaviour {

    [SerializeField]
    private AudioDatabase attackAudioDatabase;

    // Use this for initialization
    void Start () {

        attackAudioDatabase.SetAudioSource(GetComponent<AudioSource>());
    }

    private void OnTriggerEnter(Collider other) {

        if (other.gameObject.GetComponent<IsEnemy>() != null) {

            attackAudioDatabase.PlayRandom();
            Destroy(other.gameObject);
        }
    }

    // Update is called once per frame
    void Update () {
		
	}
}
