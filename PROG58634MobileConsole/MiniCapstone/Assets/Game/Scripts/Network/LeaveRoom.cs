using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LeaveRoom : MonoBehaviour
{
    public string MenuToShow = "MainMenu";

    public void Leave()
    {
        PhotonNetwork.LeaveRoom();
        UIManager.Instance.ShowOnly(MenuToShow);
    }
}
