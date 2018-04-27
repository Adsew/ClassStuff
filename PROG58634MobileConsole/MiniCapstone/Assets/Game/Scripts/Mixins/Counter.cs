using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Counter : MonoBehaviour {

    public int count = 0;

    public void Increase() {

        count++;
    }

    public void Decrease() {

        count--;
    }
}
