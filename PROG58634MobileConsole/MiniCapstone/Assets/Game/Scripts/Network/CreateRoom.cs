using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Text.RegularExpressions;

public class CreateRoom : Photon.PunBehaviour
{
    public LevelPicker picker;
    private Button createRoomBtn;
    public Text roomName;

    private void Start()
    {
        createRoomBtn = GetComponent<Button>();
    }

    public void Create()
    {
        if (roomName == null || string.IsNullOrEmpty(roomName.text))
        {
            throw new System.NullReferenceException("Cannot create room without a valid name");
        }

        LobbyManager.Instance.CreateRoom(roomName.text, TypedLobby.Default);
    }

    private void Update()
    {
        if (roomName == null)
        {
            throw new System.NullReferenceException("Room Name text must be set");
        }
        if (createRoomBtn == null)
        {
            throw new System.NullReferenceException("CreateRoom button must be set");
        }

        string str = Regex.Replace(roomName.text, @"[^0-9a-zA-Z]", "");
        if (string.IsNullOrEmpty(str))
        {
            createRoomBtn.interactable = false;
        }
        else
        {
            createRoomBtn.interactable = true;
        }
    }
}
