using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class QuitOnSelect : MonoBehaviour
{
    public void QuitApplication()
    {
        PhotonNetwork.Disconnect();
#if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = true;
#else
        Application.Quit();
#endif
    }
}
