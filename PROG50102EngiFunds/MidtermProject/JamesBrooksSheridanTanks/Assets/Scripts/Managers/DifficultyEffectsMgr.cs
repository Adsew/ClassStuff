using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DifficultyEffectsMgr : MonoBehaviour {

    private Light myLight = null;

    private Quaternion originalRot;
    private Color originalCol;

    public static DifficultyEffectsMgr This = null;

    public GameObject dirLighting;

    // Use this for initialization
    void Start() {
        
        if (This == null) {

            This = this;
        }

        if (myLight == null && dirLighting != null) {

            myLight = dirLighting.GetComponent<Light>();
            originalRot = dirLighting.transform.rotation;

            if (myLight != null) {

                originalCol = myLight.color;
            }
        }
    }

    private void AdvanceTimeUpdate() {

        if (EnemySpawnMgr.This.difficulty < EnemySpawnMgr.This.maxDifficulty && GameStateMgr.This.gameIsPlaying) {
            
            if (dirLighting != null) {

                dirLighting.transform.Rotate(Vector3.right, ((-EnemySpawnMgr.This.maxDifficulty * Time.deltaTime) / EnemySpawnMgr.This.difficultyIncTimer));

                if (myLight != null) {

                    Color color = myLight.color;

                    color.g -= 1.0f / ((EnemySpawnMgr.This.maxDifficulty / Time.deltaTime) * EnemySpawnMgr.This.difficultyIncTimer);
                    color.b -= 1.0f / ((EnemySpawnMgr.This.maxDifficulty / Time.deltaTime) * EnemySpawnMgr.This.difficultyIncTimer);

                    myLight.color = color;
                }
            }
        }
    }

    public void ResetEffects() {
        
        if (myLight != null && dirLighting != null) {

            myLight.color = originalCol;
            dirLighting.transform.rotation = originalRot;
        }
    }

    // Update is called once per frame
    void Update() {

        AdvanceTimeUpdate();
    }
}
