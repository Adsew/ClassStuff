using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UpdatePlayerName : MonoBehaviour
{
    public void UpdateName(string name)
    {
        PhotonNetwork.player.NickName = name;
    }
}
