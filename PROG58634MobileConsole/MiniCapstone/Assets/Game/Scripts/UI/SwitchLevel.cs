using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SwitchLevel : MonoBehaviour
{
    public Level switchTo;
    public string menuName;


    public void Switch()
    {
        if (switchTo == null)
        {
            LevelLoader.Instance.UnloadCurrentLevel(menuName, true);
        }
        else
        {
            LevelLoader.Instance.SwitchLevel(switchTo, menuName, true);
        }
    }
}
