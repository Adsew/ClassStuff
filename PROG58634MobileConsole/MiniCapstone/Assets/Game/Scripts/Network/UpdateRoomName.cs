using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UpdateRoomName : Photon.PunBehaviour
{
    private Text text;

    private void OnEnable()
    {
        text = GetComponent<Text>();
        if (PhotonNetwork.room != null)
        {
            text.text = "Room Name: " + PhotonNetwork.room.Name;
        }
    }
}
