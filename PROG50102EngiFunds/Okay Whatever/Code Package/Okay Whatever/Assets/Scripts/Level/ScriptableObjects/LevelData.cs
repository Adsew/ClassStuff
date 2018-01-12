using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "NewLevelData", menuName = "LevelData", order = 1)]
public class LevelData : ScriptableObject
{
    public int numberOfLives;
    public float NPCspawnTime;
    public float waitTimeOnStart = 2.0f;
    public float waitTimeOnRestart = 1.0f;
    public int jumpScpre = 10;
    public int pickupableScore = 25;
}
