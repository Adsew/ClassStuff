using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class LobbyRoom : Photon.PunBehaviour
{
    [Range(1, 30)]
    public int CountdownToStartGame;
    public Text CountdownText;
    public Button StartGameBtn;
    private float _elapsedCountdown;
    private int _sendCountdownAt;
    private bool _starting = false;

    private void OnEnable()
    {
        _elapsedCountdown = 0.0f;
        _sendCountdownAt = 0;
        _starting = false;
        _elapsedCountdown = -1;
    }

    //public override void OnJoinedRoom()
    //{
    //    UpdateCountdown();
    //}

    //public override void OnPhotonPlayerConnected(PhotonPlayer newPlayer)
    //{
    //    UpdateCountdown();
    //}

    private void UpdateCountdown()
    {
        if (PhotonNetwork.room.PlayerCount == LobbyManager.Instance.MaxPlayersPerRoom)
        {
            _elapsedCountdown = CountdownToStartGame;
            _sendCountdownAt = CountdownToStartGame;

            _starting = true;

            if (PhotonNetwork.isMasterClient)
            {
                PhotonView.Get(this).RPC("RPC_CountdownSync", PhotonTargets.Others, _elapsedCountdown);
            }
        }
        else
        {
            _elapsedCountdown = -1;
        }
    }

    public override void OnPhotonPlayerDisconnected(PhotonPlayer otherPlayer)
    {
        if (PhotonNetwork.room.PlayerCount == LobbyManager.Instance.MaxPlayersPerRoom) return;
        _elapsedCountdown = -1;

        PhotonView.Get(this).RPC("RPC_CountdownStop", PhotonTargets.Others);
    }

    //public void OnPhotonSerializeView(PhotonStream stream, PhotonMessageInfo info)
    //{
    //    if (stream.isWriting)
    //    {
    //        stream.SendNext(elapsedCountdown);
    //    }
    //    else
    //    {
    //        elapsedCountdown = (int)stream.ReceiveNext();
    //    }
    //}

    private void Update()
    {
        if (StartGameBtn == null)
        {
            throw new System.NullReferenceException("LobbyRoom requires a valid StartButton");
        }

        if (PhotonNetwork.room.PlayerCount == LobbyManager.Instance.MaxPlayersPerRoom && PhotonNetwork.isMasterClient)
        {
            StartGameBtn.interactable = true;
        }
        else
        {
            StartGameBtn.interactable = false;
        }

        if (_starting)
        {
            if (_elapsedCountdown > 0)
            {
                _elapsedCountdown -= Time.deltaTime;

                CountdownText.text = "Level Starting in " + (int)_elapsedCountdown + "...";

                if (!PhotonNetwork.isMasterClient || !(_elapsedCountdown < _sendCountdownAt)) return;
                photonView.RPC("RPC_CountdownSync", PhotonTargets.Others, _elapsedCountdown);
                _sendCountdownAt--;
            }
            else
            {
                _starting = false;
                _elapsedCountdown = float.MaxValue;
                LevelLoader.Instance.LoadLevel(LobbyManager.Instance.SelectedLevel);
                LobbyManager.Instance.StartGame();
            }
        }
        else
        {
            CountdownText.text = "Waiting for players...";
        }
    }

    public void Ready()
    {
        if (PhotonNetwork.isMasterClient)
        {
            UpdateCountdown();
        }
    }

    [PunRPC]
    public void RPC_CountdownSync(float countdown)
    {
        _elapsedCountdown = countdown;
        _starting = true;
    }

    [PunRPC]
    public void RPC_CountdownStop()
    {
        _elapsedCountdown = -1;
        _starting = false;
    }
}
