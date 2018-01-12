using UnityEngine;
using System.Collections;

public class LevelProtocol : MonoBehaviour
{
    [SerializeField]
    private LevelData _levelData;

    private static bool _paused = false;
    public static bool Paused { get { return _paused; } }

    private AudioController _audioController;

    [SerializeField]
    private CameraFollow _cameraFollow;
    [SerializeField]
    private IsCameraRig _cameraRig;
    [SerializeField]
    private IsCameraStartPoint _cameraStartPoint;
    [SerializeField]
    private IsCameraRig _camVictory;
    [SerializeField]
    private ObjectPositionTracker _tracker;
    [SerializeField]
    private IsSpawnPoint _playerSpawnPoint;

    // Use this for initialization
    void Start()
    {
        PlayerManager.Instance.playerStart = _playerSpawnPoint;

        // Initialize Camera
        if (_cameraFollow != null)
        {
            _cameraFollow.camRig = _cameraRig;
            _cameraFollow.camStartPoint = _cameraStartPoint;
            _cameraFollow.camVictory = _camVictory;
            _cameraFollow.SetCameraToStart();
            if (_playerSpawnPoint != null)
            {
                GameObject go = PlayerManager.Instance.InstantiateActivePlayer(_playerSpawnPoint.transform);
                if (go != null)
                {
                    IsPlayer player = go.GetComponent<IsPlayer>();
                    if (player != null && _tracker != null)
                    {
                        _tracker.trackObject = player.gameObject;
                    }
                    player.lives = _levelData.numberOfLives;
                    PlayerManager.Instance.UpdateUIPlayerLives(player.lives);
                    PlayerMovement playerMovement = go.GetComponent<PlayerMovement>();
                    if (playerMovement != null)
                    {
                        playerMovement.setMovementLock(true);
                    }

                }
            }
            StartCoroutine(CameraMove());
        }
        else
        {
            Debug.LogError("CameraFolow not set");
        }

        SetupManagers();
        _audioController = GetComponent<AudioController>();
        if (_audioController != null)
        {
            _audioController.PlayClip();
        }
    }

    IEnumerator CameraMove()
    {
        yield return new WaitForSeconds(_levelData.waitTimeOnStart);
        if (_cameraFollow != null)
        {
            _cameraFollow.MoveToCameraRig();
        }
        GameObject go = PlayerManager.Instance.activePlayer;
        if (go != null)
        {
            PlayerMovement playerMovement = go.GetComponent<PlayerMovement>();
            if (playerMovement != null)
            {
                playerMovement.setMovementLock(false);
            }

        }
    }

    private void SetupManagers()
    {
        EnemyManager.Instance.setSpawnDelay(_levelData.NPCspawnTime);
        ScoreManager.Instance.setPickScore(_levelData.pickupableScore);
        ScoreManager.Instance.setJumpOverScore(_levelData.jumpScpre);
        ScoreManager.Instance.resetScore();
    }

    // Update is called once per frame
    void Update()
    {

    }

    public static void PauseLevel()
    {
        _paused = true;
        Object[] objects = FindObjectsOfType<Object>();
        foreach (Object obj in objects)
        {
            GameObject go = obj as GameObject;
            if (go != null)
            {
                go.SendMessage("OnPauseLevel", SendMessageOptions.DontRequireReceiver);
            }
        }
    }

    public static void ResumeLevel()
    {
        _paused = false;
        Object[] objects = FindObjectsOfType<Object>();
        foreach (Object obj in objects)
        {
            GameObject go = obj as GameObject;
            if (go != null)
            {
                go.SendMessage("OnResumeLevel", SendMessageOptions.DontRequireReceiver);
            }
        }
        PlayerManager.Instance.ReviveActivePlayer();
    }
}
