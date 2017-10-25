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

            if (SoundMgr.This.backgroundSound2 != null) {
                
                if (EnemySpawnMgr.This.difficulty > (EnemySpawnMgr.This.maxDifficulty / 2.0f)) {
                    
                    // Scale to the dark backgroiund music in the second half of difficulty
                    float fade = (((float)EnemySpawnMgr.This.difficulty / (float)EnemySpawnMgr.This.maxDifficulty) - 0.5f )  * 2.0f;

                    if (EnemySpawnMgr.This.difficulty == EnemySpawnMgr.This.maxDifficulty){

                        fade = 1.0f;
                    }
                    
                    SoundMgr.This.CrossFadeBackgroundSound(fade);
                }
            }
        }
    }

    public void ResetEffects() {
        
        if (myLight != null && dirLighting != null) {

            myLight.color = originalCol;
            dirLighting.transform.rotation = originalRot;
        }
        if (SoundMgr.This.backgroundSound2 != null) {

            SoundMgr.This.CrossFadeBackgroundSound(0.0f);
        }
    }

    // Update is called once per frame
    void Update() {

        AdvanceTimeUpdate();
    }
}
