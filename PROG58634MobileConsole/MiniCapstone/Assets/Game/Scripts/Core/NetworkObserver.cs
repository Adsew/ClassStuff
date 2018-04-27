using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NetworkObserver : Photon.PunBehaviour
{
    public string menuOnQuit;
    public string menuOnDisconnect;
    
    public void LeaveGame()
    {
        PhotonNetwork.LeaveRoom();
        LevelLoader.Instance.UnloadCurrentLevel(menuOnQuit);
    }
    
    public override void OnPhotonPlayerDisconnected(PhotonPlayer otherPlayer)
    {
        if (LevelLoader.Instance.CurrentLevel != null)
        {
            UIManager.Instance.ShowOnly(menuOnDisconnect);
        }
    }
}
