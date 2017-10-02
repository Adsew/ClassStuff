using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterMaker : MonoBehaviour {

    public List<MonsterData> mons;

    public string fileName = "";

    public bool dump = false;
    public bool retrieve = false;
    public bool spawnAll = false;

    public GameObject monsPref;

    private MonsterContainer mc;
    

	// Use this for initialization
	void Start () {

        mc = new MonsterContainer();
	}
	
    public void dumpMonsters() {

        if (dump == true) {

            mc.saveMonsters(mons.ToArray(), fileName);

            dump = false;
        }
    }

    public void getMonsters() {

        if (retrieve == true) {

            MonsterData[] ml = mc.loadMonsters(fileName);

            mons = new List<MonsterData>();

            foreach (MonsterData m in ml) {

                mons.Add(m);
            }
            
            retrieve = false;
        }
    }

    public void spawnMonsterList() {

        if (spawnAll == true) {

            if (monsPref != null) {

                foreach (MonsterData m in mons) {
                    
                    GameObject madeMon = Instantiate(monsPref);
                    
                    Monster data = madeMon.AddComponent<Monster>();

                    data.myStats = m;
                }
            }
            spawnAll = false;
        }
    }

	// Update is called once per frame
	void Update () {

        dumpMonsters();
        getMonsters();
        spawnMonsterList();
	}
}
