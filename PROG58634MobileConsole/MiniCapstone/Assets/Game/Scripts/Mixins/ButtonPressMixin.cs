using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class ButtonPressMixin : MonoBehaviour
{
    public enum MODE
    {
        UP,
        DOWN,
        STAY
    }
    public MODE mode;
    public string buttonName;
    public UnityEvent callback = new UnityEvent();

    // Update is called once per frame
    void Update()
    {
        if (mode == MODE.DOWN)
        {
            if (Input.GetButtonDown(buttonName))
            {
                if (callback != null)
                {
                    callback.Invoke();
                }
            }
        }
        else if (mode == MODE.UP)
        {
            if (Input.GetButtonUp(buttonName))
            {
                if (callback != null)
                {
                    callback.Invoke();
                }
            }
        }
        else if (mode == MODE.STAY)
        {
            if (Input.GetButton(buttonName))
            {
                if (callback != null)
                {
                    callback.Invoke();
                }
            }
        }
    }
}
