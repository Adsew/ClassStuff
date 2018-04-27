using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LevelLoader : Singleton<LevelLoader>
{
    public float delayTime = 2.0f;
    public Level CurrentLevel { get; private set; }
    private Level _currentLevel;
    private bool finishedUnloadingLevel = false;

    public void LoadLevel(Level newLevel, bool showLoadingScreen = true, bool unloadCurrentLevel = true)
    {
        CurrentLevel = newLevel;
        StartCoroutine(LoadLevelInternal(newLevel, showLoadingScreen, unloadCurrentLevel));
    }

    IEnumerator LoadLevelInternal(Level newLevel, bool showLoadingScreen, bool unloadCurrentLevel)
    {
        Application.backgroundLoadingPriority = ThreadPriority.Low;
        if (showLoadingScreen)
        {
            UIManager.Instance.ShowLoadingScreen();
        }

        yield return new WaitForSeconds(delayTime);

        // unload current level if level is loaded
        if (unloadCurrentLevel && _currentLevel != null)
        {
            int currentIndex = 0;
            while (currentIndex >= 0 && currentIndex < _currentLevel.scenes.Count)
            {
                AsyncOperation asyncOperation = SceneManager.UnloadSceneAsync(_currentLevel.scenes[currentIndex]);
                while (!asyncOperation.isDone) yield return null;

                currentIndex++;
            }

            Debug.LogFormat("Finished unloading level: {0}", _currentLevel.levelName);
        }

        // load new level
        if (newLevel != null)
        {
            int currentIndex = 0;
            while (currentIndex >= 0 && currentIndex < newLevel.scenes.Count)
            {
                AsyncOperation asyncOperation = SceneManager.LoadSceneAsync(newLevel.scenes[currentIndex], LoadSceneMode.Additive);
                while (!asyncOperation.isDone) yield return null;
                var scene = SceneManager.GetSceneByName(newLevel.activeScene);
                if (scene.IsValid())
                {
                    SceneManager.SetActiveScene(SceneManager.GetSceneByName(newLevel.activeScene));
                }

                currentIndex++;
            }


            Debug.LogFormat("Finished loading level: {0}", newLevel.levelName);
        }

        _currentLevel = newLevel;

        yield return new WaitForSeconds(delayTime);

        if (showLoadingScreen)
        {
            UIManager.Instance.HideLoadingScreen();
        }
        Application.backgroundLoadingPriority = ThreadPriority.Normal;
    }

    public void UnloadCurrentLevel(string menuToShow, bool showLoadingScreen = true)
    {
        CurrentLevel = null;
        StartCoroutine(UnloadCurrentLevelInternal(menuToShow, showLoadingScreen));
    }

    IEnumerator UnloadCurrentLevelInternal(string menuToShow, bool showLoadingScreen)
    {
        Application.backgroundLoadingPriority = ThreadPriority.Low;

        if (showLoadingScreen)
        {
            UIManager.Instance.ShowLoadingScreen();
        }

        yield return new WaitForSeconds(delayTime);

        if (_currentLevel != null)
        {
            int currentIndex = 0;
            while (currentIndex >= 0 && currentIndex < _currentLevel.scenes.Count)
            {
                AsyncOperation asyncOperation = SceneManager.UnloadSceneAsync(_currentLevel.scenes[currentIndex]);
                while (!asyncOperation.isDone) yield return null;

                currentIndex++;
            }
        }

        _currentLevel = null;

        yield return new WaitForSeconds(delayTime);

        if (showLoadingScreen)
        {
            UIManager.Instance.HideLoadingScreen();
        }

        if (!string.IsNullOrEmpty(menuToShow))
        {
            UIManager.Instance.ShowMenu(menuToShow);
        }

        Application.backgroundLoadingPriority = ThreadPriority.Normal;

        finishedUnloadingLevel = true;
    }

    public void SwitchLevel(Level levelToLoad, string menuToShow, bool showLoadingScreen = true)
    {
        CurrentLevel = levelToLoad;
        StartCoroutine(InternalSwitchLevel(levelToLoad, menuToShow, showLoadingScreen));
    }

    IEnumerator InternalSwitchLevel(Level levelToLoad, string menuToShow, bool showLoadingScreen)
    {
        finishedUnloadingLevel = false;
        StartCoroutine(UnloadCurrentLevelInternal(menuToShow, showLoadingScreen));

        while (!finishedUnloadingLevel)
        {
            yield return null;
        }

        StartCoroutine(LoadLevelInternal(levelToLoad, showLoadingScreen, true));
    }
}
