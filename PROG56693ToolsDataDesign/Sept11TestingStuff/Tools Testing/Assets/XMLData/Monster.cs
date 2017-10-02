using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Xml;
using System.Xml.Serialization;

[System.Serializable]
public class MonsterData {

    [XmlAttribute("name")]
    public string monsterName;

    [XmlElement("health")]
    public int health;
}

public class Monster : MonoBehaviour {

    public MonsterData myStats;

    void Start() {
        
    }

    void Update() {
        
    }
}