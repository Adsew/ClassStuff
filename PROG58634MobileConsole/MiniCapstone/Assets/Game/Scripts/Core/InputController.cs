using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

// reference: https://docs.unity3d.com/Manual/iphone-joystick.html
public class InputController : Singleton<InputController>
{
    public UnityEvent OnConnectionChange;
    public bool Connected { get; private set; }
    public float delay = 1.0f;

    private void Awake()
    {
        StartCoroutine(CheckForControllers());
    }

    IEnumerator CheckForControllers()
    {
        while (true)
        {
            var controllers = Input.GetJoystickNames();
            if (!Connected && controllers.Length > 0)
            {
                Connected = true;
                OnConnectionChange.Invoke();
                Debug.Log("Connected");
            }
            else if (Connected && controllers.Length == 0)
            {
                Connected = false;
                OnConnectionChange.Invoke();
                Debug.Log("Disconnected");
            }
            yield return new WaitForSeconds(delay);
        }
    }

}
