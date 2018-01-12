using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using System.IO;

public class LevelManager : MonoBehaviour
{
    //-----------------------------
    //  LevelManager Singleton
    //
    private static LevelManager _instance;
    public static LevelManager Instance
    {
        get { return _instance; }
    }
    //------------------------------
    //  GlobalScene property
    //
    private Scene _globalScene;
    public Scene GlobalScene
    {
        get { return _globalScene; }
    }

    // Current Scene for level
    private Scene _currentScene;

    // The max load progress value (0 -> 0.9f Loading)(0.9 -> 1.0f Activation)
    public static float AsyncLoadMax = 0.9f;

    // Used for Async Loading
    public IsUIPanel loadingPanel;
    public Slider loadingSlider;
    public TextMeshProUGUI loadingText;

    // Use this for initialization
    void Start()
    {
        if (_instance == null)
        {
            _instance = this;
        }
        else
        {
            Destroy(this);
        }

        List<string> levels = BundleManager.Instance.LoadScenes("levels");
        IsUIPanel panel = UIManager.Instance.GetPanelById(1);
        if (panel != null)
        {
            IsLevelSelect levelSelect = panel.GetComponentInChildren<IsLevelSelect>();
            if (levelSelect != null)
            {
                int i = 1;
                foreach (string levelPath in levels)
                {
                    string levelName = Path.GetFileNameWithoutExtension(levelPath);
                    levelSelect.AddButton(levelName, i);
                    ++i;
                }
            }
        }


        // add onsceneload and onsceneunload functions to SceneManager callbacks
        SceneManager.sceneLoaded += OnSceneLoaded;
        SceneManager.sceneUnloaded += OnSceneUnloaded;

        _globalScene = SceneManager.GetSceneByName("GLOBAL");
    }

    // Update is called once per frame
    void Update()
    {

    }

    // Load level by string name
    public void LoadLevel(string name)
    {
        Debug.Log("LevelManager::LoadLevel(): " + name);
        SceneManager.LoadScene(name, LoadSceneMode.Additive);
    }

    // Load level by string name using async operations
    public void LoadLevelAsync(string name)
    {
        Debug.Log("LevelManager::LoadLevelAsync() started: " + name);
        StartCoroutine(InternalLoadLevelAsync(name));
        Debug.Log("LevelManager::LoadLevelAsync() finished: " + name);
    }

    // Unload the current scene
    public void UnloadCurrentLevel()
    {
        SceneManager.UnloadSceneAsync(_currentScene);
    }

    public void OnSceneLoaded(Scene scene, LoadSceneMode mode)
    {
        Debug.Log("LevelManager::OnSceneLoaded(): " + scene.ToString());
        // make sure new GameObjects are added to gameplay scene not the global scene
        _currentScene = scene;
        SceneManager.SetActiveScene(scene);
    }

    public void OnSceneUnloaded(Scene scene)
    {
        Debug.Log("LevelManager::OnSceneUnloaded(): " + scene.ToString());
        SceneManager.SetActiveScene(_globalScene);
    }

    private IEnumerator InternalLoadLevelAsync(string name)
    {

        AsyncOperation operation = SceneManager.LoadSceneAsync(name, LoadSceneMode.Additive);
        Debug.Log("LoadingLevel::LoadLevel() loading level async: " + operation.progress);
        while (!operation.isDone)
        {
            float asyncOpProgress = operation.progress / LevelManager.AsyncLoadMax;
            if (loadingSlider == null)
            {
                Debug.LogError("LoadingLevel::LoadLevelAsync() found no loading slider");
                yield return null;
            }
            else
            {
                Debug.Log("LoadingLevel::LoadLevel() updating UI: " + operation.progress);
                loadingSlider.value = asyncOpProgress;
                if (loadingText != null)
                {
                    loadingText.text = (asyncOpProgress * 100.0f).ToString() + "%";
                }
            }
            Debug.Log("LoadingLevel::LoadLevel() progress: " + operation.progress);
            UIManager.Instance.DeactivateAllPanels();

            yield return null;
        }
    }
}
