using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LightOn : MonoBehaviour
{

    public GameObject fire;

    public void lightOn()
    {
        if (fire != null)
        {
            fire.SetActive(true);
        }
    }
}
