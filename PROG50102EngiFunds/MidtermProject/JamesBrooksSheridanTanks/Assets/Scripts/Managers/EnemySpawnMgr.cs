using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemySpawnMgr : MonoBehaviour {

    private int lastSpawnTime = 0;

    private int difficulty = 1;

    public List<Enemy> activeEnemies { get; private set; }

    public static EnemySpawnMgr This;

    [Range(10, 60)]
    public double difficultyIncTimer = 30.0;    // Seconds

    [Range(2, 60)]
    public int spawnInterval = 10;              // Seconds

    [Range(0, 100)]
    public int airTankSpawnChance = 40;         // Chance for air tank to spawn over ground

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

        if (activeEnemies == null) {

            activeEnemies = new List<Enemy>();
        }
    }
	
    public void ResetToBase() {

        foreach (Enemy e in activeEnemies) {

            Destroy(e.gameObject);
        }

        activeEnemies.Clear();

        foreach (GameObject path in groundPaths) {

            Spline s = path.GetComponent<Spline>();

            if (s != null) {

                s.RemoveAllHeads();
            }
        }

        foreach (GameObject path in airPaths) {

            Spline s = path.GetComponent<Spline>();

            if (s != null) {

                s.RemoveAllHeads();
            }
        }

        lastSpawnTime = 0;
    }

    public void GameStartSpawns() {

        if (groundTank != null) {

            foreach (GameObject path in groundPaths) {

                if (path != null) {

                    Spline spline = path.GetComponent<Spline>();

                    if (spline != null) {

                        GameObject tank = Instantiate(groundTank, groundTank.transform.position, groundTank.transform.rotation);

                        if (tank != null) {

                            Enemy tankProperties = tank.GetComponent<Enemy>();

                            if (tankProperties != null) {

                                spline.AddHead(tank);
                                activeEnemies.Add(tankProperties);
                                tankProperties.myPath = spline;
                            }
                            else {

                                Destroy(tank);
                            }
                        }
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

                        if (tank != null) {

                            Enemy tankProperties = tank.GetComponent<Enemy>();

                            if (tankProperties != null) {

                                spline.AddHead(tank);
                                activeEnemies.Add(tankProperties);
                                tankProperties.myPath = spline;
                            }
                            else {

                                Destroy(tank);
                            }
                        }
                    }
                }
            }
        }

        lastSpawnTime = (int)GameStateMgr.This.gameTime;
    }

    private void RandomSpawnOnInterval() {

        if (GameStateMgr.This.gameIsPlaying && ((int)GameStateMgr.This.gameTime - lastSpawnTime) >= spawnInterval) {

            if (groundTank != null && airTank != null) {

                GameObject tankToSpawn = null;
                List<GameObject> splinesForTankSpawn = null;

                int chance = Random.Range(1, 101);
                
                // Spawn ground tank
                if (chance > airTankSpawnChance) {

                    tankToSpawn = groundTank;
                    splinesForTankSpawn = groundPaths;
                }
                // Spawn air tank
                else {

                    tankToSpawn = airTank;
                    splinesForTankSpawn = airPaths;
                }

                if (tankToSpawn != null && splinesForTankSpawn != null) {
                    if (splinesForTankSpawn.Count > 0) {

                        chance = Random.Range(0, splinesForTankSpawn.Count);

                        Spline spline = splinesForTankSpawn[chance].GetComponent<Spline>();

                        if (spline != null) {

                            GameObject tank = Instantiate(
                            tankToSpawn,
                            splinesForTankSpawn[chance].transform.position,
                            tankToSpawn.transform.rotation
                            );

                            if (tank != null) {

                                Enemy tankProperties = tank.GetComponent<Enemy>();

                                if (tankProperties != null) {

                                    spline.AddHead(tank);
                                    activeEnemies.Add(tankProperties);
                                    tankProperties.myPath = spline;
                                }
                                else {

                                    Destroy(tank);
                                }
                            }
                        }
                    }
                }
            }

            lastSpawnTime = (int)GameStateMgr.This.gameTime;
        }
    }

    public void RemoveDeadEnemy(Enemy deadEnemy) {

        if (activeEnemies != null) {

            activeEnemies.Remove(deadEnemy);
        }
    }

    // Every x time increases the difficulty
    public int DetermineDifficulty() {

        int d = (int)(GameStateMgr.This.gameTime / difficultyIncTimer) + 1;

        // Max 10 (rotation aim speed maxes at 10)
        if (d > 9) {

            d = 9;
        }

        return d;
    }

    // Let the player know if the difficulty changes
    private void DifficultyUpdate() {

        int curDif = DetermineDifficulty();

        if (difficulty != curDif) {

            difficulty = curDif;

            DisplayMgr.This.UpdateMessage("Difficulty has changed to " + difficulty + "!");
        }
    }

	// Update is called once per frame
	void Update () {

        RandomSpawnOnInterval();
        DifficultyUpdate();
	}
}
