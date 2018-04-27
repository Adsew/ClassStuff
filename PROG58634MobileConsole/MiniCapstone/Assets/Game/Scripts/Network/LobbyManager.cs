using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LobbyManager : NetworkSingleton<LobbyManager>
{

    #region Public Variables

    /// <summary>
    /// The PUN loglevel. 
    /// </summary>
    public PhotonLogLevel Loglevel = PhotonLogLevel.Informational;

    /// <summary>
    /// The maximum number of players per room. When a room is full, it can't be joined by new players, and so new room will be created.
    /// </summary>   
    [Tooltip("The maximum number of players per room. When a room is full, it can't be joined by new players, and so new room will be created")]
    public byte MaxPlayersPerRoom = 4;

    public string MainMenu;
    public string RoomMenu;

    //[Tooltip("The points where the config properties are set.")]
    //public List<Transform> lobbyStartPoints = new List<Transform>();

    public List<Level> Levels = new List<Level>();
    [HideInInspector]
    public Level SelectedLevel;
    public Character SelectedCharacter { get; set; }
    public NetworkSpawner NetworkSpawner;

    public string FailedRoomUIMenu = "CreateRoomFailed";
    #endregion


    #region Private Variables

    /// <summary>
    /// This client's version number. Users are separated from each other by gameversion (which allows you to make breaking changes).
    /// </summary>
    private const string GameVersion = "1";
    
    private int _inGameReadyCounter = 0;

    #endregion


    #region MonoBehaviour CallBacks


    /// <summary>
    /// MonoBehaviour method called on GameObject by Unity during early initialization phase.
    /// </summary>
    private void Awake()
    {
        // #NotImportant
        // Force LogLevel
        PhotonNetwork.logLevel = Loglevel;

        // #Critical
        // we don't join the lobby. There is no need to join a lobby to get the list of rooms.
        PhotonNetwork.autoJoinLobby = false;


        // #Critical
        // this makes sure we can use PhotonNetwork.LoadLevel() on the master client and all clients in the same room sync their level automatically
        PhotonNetwork.automaticallySyncScene = true;
    }

    private void Start()
    {
        Connect();
    }
    #endregion


    #region Public Methods

    [PunRPC]
    public void OnReadyToSpawn()
    {
        _inGameReadyCounter++;
    }
    
    private IEnumerator InternalStartGame()
    {
        Debug.Log("Starting internal start Game");
        // check that the active scene is the levels active scene so that the game can spawn in required elements
        var currentLevel = LevelLoader.Instance.CurrentLevel;
        if (currentLevel != null)
        {
            Debug.Log("Waiting for current levels active scene to load");
            var desiredActive = SceneManager.GetSceneByName(currentLevel.activeScene);
            while (!desiredActive.IsValid())
            {
                desiredActive = SceneManager.GetSceneByName(currentLevel.activeScene);
                yield return null;
            }
            Debug.Log("Finished waiting for current levels active scene to load");
            var active = SceneManager.GetActiveScene();
            Debug.Log("Checking active scene");
            Debug.Log("Desired Scene: " + desiredActive.name + " Current Active: " + active.name);
            // wait until we are in the desired scene and have a reference to the network spawner
            while (desiredActive != active)
            {
                active = SceneManager.GetActiveScene();
                yield return null;
            }

            // send message that this client is ready
            photonView.RPC("OnReadyToSpawn", PhotonTargets.All);

            Debug.Log("Checking ready count");
            // wait until ready count is the number of the room size
            while (_inGameReadyCounter != PhotonNetwork.room.MaxPlayers)
            {
                yield return null;
            }
            Debug.Log("Finished checking ready count");
            Debug.Log("Checking network spawner");
            while (NetworkSpawner == null)
            {
                yield return null;
            }
            Debug.Log("Finished Checking network spawner");
            // spawn once everyone is ready
            if (NetworkSpawner != null)
            {
                Debug.Log("Spawning");
                NetworkSpawner.Spawn();
            }
        }
    }
    
    public void StartGame()
    {
        Debug.Log("Start Game");
        _inGameReadyCounter = 0;
        NetworkSpawner = null;
        StartCoroutine(InternalStartGame());
    }

    public void EndGame()
    {
        Debug.Log("End Game");
        _inGameReadyCounter = 0;
        NetworkSpawner = null;
    }

    /// <summary>
    /// Start the connection process. 
    /// - If already connected, we attempt joining a random room
    /// - if not yet connected, Connect this application instance to Photon Cloud Network
    /// </summary>
    private void Connect()
    {
        Debug.Assert(!PhotonNetwork.connected, "Cannot connect if already connected to Photon.");
        // we check if we are connected or not, we join if we are , else we initiate the connection to the server.
        if (!PhotonNetwork.connected)
        {
            StartCoroutine(InternalConnect());
        }
    }

    private IEnumerator InternalConnect()
    {
        UIManager.Instance.ShowLoadingScreen();
        PhotonNetwork.ConnectUsingSettings(GameVersion);
        while (!PhotonNetwork.connected) { yield return null; }
        UIManager.Instance.HideLoadingScreen();
    }

    public void CreateRoom(string name, TypedLobby lobby)
    {
        var options = new RoomOptions() { IsVisible = true, IsOpen = true, MaxPlayers = MaxPlayersPerRoom };
        PhotonNetwork.CreateRoom(name, options, lobby);
    }

    public void JoinRandomRoom()
    {
        UIManager.Instance.ShowLoadingScreen();
        PhotonNetwork.JoinRandomRoom();
    }

    public static void JoinRoom(string name)
    {
        UIManager.Instance.ShowLoadingScreen();
        PhotonNetwork.JoinRoom(name);
    }

    public static void LeaveRoom()
    {
        UIManager.Instance.ShowLoadingScreen();
        PhotonNetwork.LeaveRoom();
    }
    #endregion

    #region Photon.PunBehaviour CallBacks


    public override void OnConnectedToMaster()
    {
        Debug.Log("DemoAnimator/Launcher: OnConnectedToMaster() was called by PUN");

        PhotonNetwork.automaticallySyncScene = false;
        PhotonNetwork.JoinLobby(TypedLobby.Default);
    }

    public override void OnDisconnectedFromPhoton()
    {
        Debug.LogWarning("DemoAnimator/Launcher: OnDisconnectedFromPhoton() was called by PUN");
    }

    public override void OnPhotonRandomJoinFailed(object[] codeAndMsg)
    {
        Debug.Log("DemoAnimator/Launcher:OnPhotonRandomJoinFailed() was called by PUN. No random room available, so we create one.\nCalling: PhotonNetwork.CreateRoom(null, new RoomOptions() {maxPlayers = 4}, null);");
        // #Critical: we failed to join a random room, maybe none exists or they are all full. No worries, we create a new room.
    }

    public override void OnPhotonPlayerConnected(PhotonPlayer newPlayer)
    {
        UpdateRoomStats();
    }

    public override void OnPhotonPlayerDisconnected(PhotonPlayer otherPlayer)
    {
        UpdateRoomStats();
    }

    private void UpdateRoomStats()
    {
        // check that this is the master client and in a room
        if (!PhotonNetwork.inRoom || !PhotonNetwork.isMasterClient) return;
        // check that we have the required number of players to start game
        if (PhotonNetwork.room.PlayerCount == MaxPlayersPerRoom)
        {
            PhotonNetwork.room.IsOpen = false;
            PhotonNetwork.room.IsVisible = false;
        }
        else
        {
            PhotonNetwork.room.IsOpen = true;
            PhotonNetwork.room.IsVisible = true;
        }
    }

    public override void OnPhotonCreateRoomFailed(object[] codeAndMsg)
    {
        UIManager.Instance.ShowOnly(FailedRoomUIMenu);
    }

    public override void OnCreatedRoom()
    {
        if (SelectedLevel == null)
        {
            throw new System.NullReferenceException("Cannot create room without a selected level");
        }

        var table = new ExitGames.Client.Photon.Hashtable
        {
            { "LevelName", SelectedLevel.levelName }
        };
        UIManager.Instance.ShowLoadingScreen();
        PhotonNetwork.room.SetCustomProperties(table, null, false);
    }

    private void OnGUI()
    {
        GUILayout.Label(PhotonNetwork.connectionStateDetailed.ToString());
    }

    public override void OnJoinedRoom()
    {
        Debug.Log("DemoAnimator/Launcher: OnJoinedRoom() called by PUN. Now this client is in a room.");

        string levelName = (string)PhotonNetwork.room.CustomProperties["LevelName"];
        SelectedLevel = Levels.Find(item => item.levelName.Equals(levelName));
        if (SelectedLevel == null)
        {
            Debug.LogError("Could not find rooms currernt level. Exiting Room...");
            PhotonNetwork.LeaveRoom();
        }
        else
        {
            UIManager.Instance.ShowOnly(RoomMenu);
            UIManager.Instance.HideLoadingScreen();
        }
    }

    //public override void OnLeftRoom()
    //{
    //    UIManager.Instance.ShowOnly(MainMenu);
    //    UIManager.Instance.HideLoadingScreen();
    //}


    #endregion
}
