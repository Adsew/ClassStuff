using UnityEngine;

public class GameStateManager : MonoBehaviour
{

    private static GameStateManager _instance;
    public static GameStateManager Instance
    { get { return _instance; } }
    private Animator _animator;

    //
    //  FSM trigger names
    //
    public static string mainMenu = "ToStartScreen";
    public static string characterSelect = "ToCharacterSelect";
    public static string levelSelect = "ToSelectLevel";
    public static string inGame = "ToInGame";
    public static string playerDied = "ToPlayerDied";
    public static string playerWon = "ToPlayerWon";
    public static string gameOver = "ToGameOver";
    public static string pauseMenu = "ToPauseMenu";
    public static string endLevel = "EndLevel";

    private void Awake()
    {
        if (_instance == null)
        {
            _instance = this;
            _animator = gameObject.GetComponent<Animator>();
            Debug.Assert(_animator != null);
        }
        else
        {
            Destroy(gameObject);
        }
    }

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    public void SetTrigger(string triggerName)
    {
        Debug.Assert(_animator != null);
        _animator.SetTrigger(triggerName);
    }

    public void GoToInGame(string levelName)
    {
        Debug.Assert(_animator != null);
        _animator.SetTrigger(inGame);
        LevelManager.Instance.LoadLevel(levelName);
    }

    public void QuitGame()
    {
        Debug.Log("Quit Game");
        Application.Quit();
    }
}
