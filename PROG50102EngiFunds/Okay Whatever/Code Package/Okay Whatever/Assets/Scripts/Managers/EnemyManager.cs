using UnityEngine;
using System.Collections.Generic;
using System;

public class EnemyManager : MonoBehaviour
{
    private const string BARREL_SPLINE_OBJ_NAME = "Graph_Barrel";
    private const string FIRE_SPLINE_OBJ_NAME = "Graph_Fire";

    //-----------------------------
    //  EnemyManager Singleton
    //
    private static EnemyManager _instance;
    public static EnemyManager Instance
    {
        get { return _instance; }
    }

    public GameObject barrelPrefab;
    public GameObject firePrefab;

    private SplinesSpawner mBarrelPath;
    private SplinesSpawner mFirePath;

    private EnemyCommands mEnemyCommands;

    //This value should be setted by LevelProtocol
    private float timeBetweenSpawns = 8;
    private float spawnCountDown = 5;

    private bool isRunning = true;

    private List<GameObject> mEnemysAlive = new List<GameObject>();

    private GameObject mFireEnemy;
    private GameObject mFireBarrel;

    public void setSpawnDelay(float nPCspawnTime)
    {
        timeBetweenSpawns = nPCspawnTime;
    }

    // Use this for initialization
    void Start()
    {
        if (_instance == null)
        {
            _instance = this;
        }
        else
        {
            Destroy(this);
        }
    }

    private void Update()
    {
        if (isRunning)
        {
            barrelSpawnCheck();
        }
    }

    private void barrelSpawnCheck()
    {
        spawnCountDown -= Time.deltaTime;
        if (spawnCountDown < 0)
        {
            spawnCountDown += timeBetweenSpawns;
            if (mEnemyCommands != null)
            {
                mEnemyCommands.spawnBarrel();
            }
        }
    }

    public void setBossScript(EnemyCommands enemyCommands)
    {
        mEnemyCommands = enemyCommands;
    }

    public void addBarrelToSpline(GameObject barrel)
    {
        if (mBarrelPath == null)
        {
            setSpawners();
        }
        if (mBarrelPath != null && barrelPrefab != null)
        {
            mBarrelPath.spawnObject(barrel);
        }
    }

    public void spawnFire()
    {
        if (mFireEnemy == null)
        {
            if (mFirePath == null)
            {
                setSpawners();
            }
            if (mFirePath != null && firePrefab != null)
            {
                mFireEnemy = Instantiate(firePrefab);
                mFirePath.spawnObject(mFireEnemy);
            }
        }
    }

    private void setSpawners()
    {
        GameObject graphGameObject = GameObject.Find(BARREL_SPLINE_OBJ_NAME);
        mBarrelPath = graphGameObject.GetComponent<SplinesSpawner>();

        GameObject graphFire = GameObject.Find(FIRE_SPLINE_OBJ_NAME);
        mFirePath = graphFire.GetComponent<SplinesSpawner>();
    }

    // called when game starts InPlaying state
    public void OnResumeLevel()
    {
        isRunning = true;
    }

    // Called when game exits InPlayingState
    public void OnPauseLevel()
    {
        isRunning = false;
    }

    // Called when the player died
    public void PlayerDied()
    {
        destroyAllEnemies();
        isRunning = false;
    }

    // Called when the player won
    public void PlayerWon()
    {
        destroyAllEnemies();
        isRunning = false;
    }

    public void registerEnemy(GameObject obj)
    {
        mEnemysAlive.Add(obj);
    }

    public void removeEnemy(GameObject obj)
    {
        mEnemysAlive.Remove(obj);
    }

    private void destroyAllEnemies()
    {
        foreach (GameObject obj in mEnemysAlive)
        {
            if (obj != null)
            {
                IsEnemy es = obj.GetComponent<IsEnemy>();
                if (es.type != IsEnemy.ENEMY_TYPE.FIRE_BARREL)
                {
                    Destroy(obj);
                }
            }
        }
    }

    public void barrelReachedEnd(GameObject barrel)
    {
        spawnFire();
        if (mFireBarrel != null)
        {
            mFireBarrel.SendMessage("lightOn");
        }
    }


    public void setFireBarrel(GameObject gameObject)
    {
        mFireBarrel = gameObject;
    }
}
