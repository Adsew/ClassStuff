using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NetworkSingleton<T> : Photon.PunBehaviour where T : Photon.PunBehaviour
{
    private static T _instance;
    private static bool _appFinished = false;

    public static T Instance
    {
        get
        {
            if (_appFinished)
            {
                Debug.LogErrorFormat("Accessing Singleton ({0}) after app finished!", typeof(T).ToString());
                return null;
            }

            if (_instance == null)
            {
                _instance = FindObjectOfType<T>();

                if (_instance == null)
                {
                    Debug.LogError("Singleton with the name '" + typeof(T).ToString() + "' was not found is scene!");
                }
            }

            return _instance;
        }
    }

    private void OnDestroy()
    {
        _appFinished = true;
    }
}
