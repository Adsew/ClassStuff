using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MObjectSpawner : MonoBehaviour {

    private Transform trans = null;

    public GameObject objToSpawn = null;

    [Range(0,3)]
    public int facingDir = 0;    // Required to stop blend tree from shooting multiple events

    private void Start() {

        if (trans == null) {

            trans = transform;
        }
    }
    
    // General spawning function
    public void Spawn() {
        
        if (objToSpawn != null) {

            Instantiate(objToSpawn, transform);
        }
    }
    
    // Specialized spawner to send an object in the specified direction of the player
    public void SpawnWithPositionRotationVelocity(AnimationEvent animEvent) {
        
        if (objToSpawn != null && trans != null && facingDir == animEvent.intParameter) {

            GameObject newObj = Instantiate(objToSpawn, trans.position, new Quaternion());

            newObj.transform.Rotate(Vector3.forward, animEvent.floatParameter);

            Rigidbody2D rb = newObj.GetComponent<Rigidbody2D>();

            if (rb != null){

                Vector2 v = new Vector2();

                v.x = -newObj.transform.up.x;
                v.y = -newObj.transform.up.y;

                rb.velocity = v;
            }
        }
    }
}
