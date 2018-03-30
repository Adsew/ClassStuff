using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;


/// <summary>
/// Majority code from Unity's multiplayer tutorial
/// </summary>
public class PlayerController : NetworkBehaviour {

    public GameObject bulletPrefab = null;
    public Transform bulletSpawnPoint = null;

    public Vector3 cameraDistance = new Vector3(0.0f, 2.0f, -6.0f);

    public override void OnStartLocalPlayer() {

        GetComponent<MeshRenderer>().material.color = Color.blue;

        Camera.main.transform.parent = transform;
        Camera.main.transform.localPosition = cameraDistance;
    }

    // Update is called once per frame
    void Update () {

        if (!isLocalPlayer) {

            return;
        }

        if (Input.GetKeyDown(KeyCode.Space)) {

            CmdFire();
        }

        var x = Input.GetAxis("Horizontal") * Time.deltaTime * 150.0f;
        var z = Input.GetAxis("Vertical") * Time.deltaTime * 3.0f;

        transform.Rotate(0, x, 0);
        transform.Translate(0, 0, z);
    }

    [Command]
    void CmdFire() {

        // Create the Bullet from the Bullet Prefab
        GameObject bullet = (GameObject)Instantiate(
            bulletPrefab,
            bulletSpawnPoint.position,
            bulletSpawnPoint.rotation);

        // Add velocity to the bullet
        bullet.GetComponent<Rigidbody>().velocity = bullet.transform.forward * 6;

        // Spawn the bullet on the Clients
        NetworkServer.Spawn(bullet);

        // Destroy the bullet after 2 seconds
        Destroy(bullet, 2.0f);
    }
}
