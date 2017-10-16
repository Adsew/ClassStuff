using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemySpawnMgr : MonoBehaviour {

    private List<GameObject> activeEnemies;

    private int difficult = 1;
    private int lastSpawnTime = 0;

    public static EnemySpawnMgr This;

    [Range(10, 60)]
    public double difficultyIncTimer = 30.0;    // Seconds

    [Range(2, 60)]
    public int spawnInterval = 10;         // Seconds

    public GameObject groundTank;
    public GameObject airTank;

    public List<GameObject> groundPaths;
    public List<GameObject> airPaths;

	// Use this for initialization
	void Start () {

        if (This == null) {

            This = this;
        }

        if (groundPaths == null) {

            groundPaths = new List<GameObject>();
        }

        if (airPaths == null) {

            airPaths = new List<GameObject>();
        }
    }
	
    public void GameStartSpawns() {

        if (groundTank != null) {

            foreach (GameObject path in groundPaths) {

                if (path != null) {

                    Spline spline = path.GetComponent<Spline>();

                    if (spline != null) {

                        GameObject tank = Instantiate(groundTank, groundTank.transform.position, groundTank.transform.rotation);
                        spline.AddHead(tank);
                        activeEnemies.Add(tank);
                    }
                }
            }
        }

        if (airTank != null) {

            foreach (GameObject path in airPaths) {

                if (path != null) {

                    Spline spline = path.GetComponent<Spline>();

                    if (spline != null) {

                        GameObject tank = Instantiate(airTank, path.transform.position, airTank.transform.rotation);
                        spline.AddHead(tank);
                        activeEnemies.Add(tank);
                    }
                }
            }
        }

        lastSpawnTime = (int)GameStateMgr.This.gameTime;
    }

    private void randomSpawnOnInterval() {

        if (GameStateMgr.This.gameIsPlaying && ((int)GameStateMgr.This.gameTime - lastSpawnTime) >= spawnInterval) {

            // Spawn object

            lastSpawnTime = (int)GameStateMgr.This.gameTime;
        }
    }

    // Every x time increases the difficulty
    public int DetermineDifficulty() {

        return (int)(GameStateMgr.This.gameTime / difficultyIncTimer);
    }

	// Update is called once per frame
	void Update () {

        randomSpawnOnInterval();
	}
}
