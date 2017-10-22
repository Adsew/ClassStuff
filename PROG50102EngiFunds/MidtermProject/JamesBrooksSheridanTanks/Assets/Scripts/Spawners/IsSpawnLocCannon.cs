using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsSpawnLocCannon : IsSpawnLoc {

    protected AudioSource audSrc;

    // Use this for initialization
    void Start() {

        InitSpawnLoc();

        if (audSrc == null) {

            audSrc = this.gameObject.AddComponent<AudioSource>();
            audSrc.playOnAwake = false;
        }
    }

    public new IsProjectile SpawnObject() {

        if (objToSpawn != null) {

            GameObject temp = Instantiate(objToSpawn,
                myTransform.position + this.gameObject.transform.forward,
                myTransform.rotation);

            if (SoundMgr.This.InEarshotOfPlayer(this.gameObject.transform.position)) {

                SoundMgr.This.PlayRandomCannonFireSound(audSrc);
            }

            return temp.GetComponent<IsProjectile>();
        }

        return null;
    }

    // Update is called once per frame
    void Update() {

    }
}
