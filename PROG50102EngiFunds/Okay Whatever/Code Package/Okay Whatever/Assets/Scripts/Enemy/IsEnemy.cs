using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsEnemy : MonoBehaviour
{
    public enum ENEMY_TYPE { FIRE, BARREL, FIRE_BARREL }

    public ENEMY_TYPE type;

    // Use this for initialization
    void Start()
    {
        EnemyManager.Instance.registerEnemy(this.gameObject);
        if (type == ENEMY_TYPE.FIRE_BARREL)
        {
            EnemyManager.Instance.setFireBarrel(this.gameObject);
        }
    }
}
