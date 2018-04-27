using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class RoomListing : MonoBehaviour
{
    public string RoomName { get; private set; }
    public bool Valid { get; set; }
    public LobbyView lobbyView;
    [SerializeField]
    private Text roomName;
    private Button joinBtn;

    private void Start()
    {
        joinBtn = GetComponent<Button>();
    }

    public void SetRoomName(string name)
    {
        if (roomName == null)
        {
            throw new System.NullReferenceException("Found null while setting room name text");
        }

        RoomName = name;
        roomName.text = name;
    }

    public void JoinRoom()
    {
        LobbyManager.JoinRoom(RoomName);
    }

    public void Update()
    {
        if (joinBtn == null)
        {
            throw new System.NullReferenceException("Null JoinButton found while checking if JoinRoom is viable");
        }

        joinBtn.interactable = !string.IsNullOrEmpty(PhotonNetwork.player.NickName);
    }
}
