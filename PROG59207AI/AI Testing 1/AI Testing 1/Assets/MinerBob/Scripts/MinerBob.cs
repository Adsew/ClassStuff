using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MinerBob : MonoBehaviour {

    public Animator FSMAI;

    public float comfortLevel = 50.0f;
    public float maxNuggets = 20.0f;
    public float thirstThreshold = 50.0f;
    public float tirednessThreshold = 50.0f;
    public float lifeSpan = 100.0f;
    
    public float currentGold = 0.0f;
    public float bankAccount = 0.0f;
    public float thirstLevel = 0.0f;
    public float fatigueLevel = 0.0f;
    public float currentAge = 15.0f;
    
    public void sleep(float restSpeed) {

        fatigueLevel += restSpeed;

        if (fatigueLevel < 0.0f) {

            fatigueLevel = 0.0f;
        }
    }

    public void drink(float consumption, float cost) {

        currentGold -= cost;
        thirstLevel -= consumption;
    }

    public void mine(float amount, float fatigue, float thirst) {

        currentGold += amount;
        fatigueLevel += fatigue;
        thirstLevel += thirst;
    }

    public void deposit(float amount) {

        currentGold -= amount;
        bankAccount += amount;
    }

    public void age(float years) {

        currentAge += years;
    }
}
