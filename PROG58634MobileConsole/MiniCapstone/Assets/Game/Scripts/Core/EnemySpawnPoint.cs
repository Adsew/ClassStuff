using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemySpawnPoint : Photon.PunBehaviour {

    public string resourceToSpawn = "";

    public void Spawn()
    {
        if (PhotonNetwork.isMasterClient)
        {
            PhotonNetwork.Instantiate(resourceToSpawn, transform.position, transform.rotation, 0);
        }
    }
}
