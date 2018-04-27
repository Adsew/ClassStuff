using System;
using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;

[Obsolete("Use LevelLoader. Any single scene Loading should only be done in core.", true)]
public class SceneLoader : Singleton<SceneLoader>
{
    public float delayTime = 1.0f;

    private int currentSceneBuildIndex = -1;

    public void LoadScene(string sceneName, bool showLoadingScreen = true, string unloadScene = "", bool unloadCurrentScene = false)
    {
        StartCoroutine(LoadSceneInternal(sceneName, showLoadingScreen, unloadScene, unloadCurrentScene));
    }

    public void UnloadScene(string sceneName, bool showLoadingScreen = true)
    {
        StartCoroutine(UnloadSceneInternal(sceneName, showLoadingScreen));
    }

    private IEnumerator LoadSceneInternal(string sceneName, bool showLoadingScreen, string unloadScene, bool unloadCurrentScene)
    {
        Application.backgroundLoadingPriority = ThreadPriority.Low;

        if (showLoadingScreen)
        {
            UIManager.Instance.ShowLoadingScreen();
        }

        yield return new WaitForSeconds(delayTime);

        AsyncOperation asyncOperation = null;

        // Unload current scene (build index 0 is reserved for core and cannot be unloaded)
        if (currentSceneBuildIndex > 0)
        {
            asyncOperation = SceneManager.UnloadSceneAsync(currentSceneBuildIndex);
            while (!asyncOperation.isDone) yield return null;
        }

        // Unload the scene to unload
        Scene scene = SceneManager.GetSceneByName(unloadScene);
        if (scene.IsValid() && scene.isLoaded)
        {
            asyncOperation = SceneManager.UnloadSceneAsync(unloadScene);
            while (!asyncOperation.isDone) yield return null;
        }

        // load the new scene
        asyncOperation = SceneManager.LoadSceneAsync(sceneName, LoadSceneMode.Additive);
        while (!asyncOperation.isDone) yield return null;

        scene = SceneManager.GetSceneByName(sceneName);
        SceneManager.SetActiveScene(scene);

        currentSceneBuildIndex = scene.buildIndex;

        yield return new WaitForSeconds(delayTime);

        if (showLoadingScreen)
        {
            UIManager.Instance.HideLoadingScreen();
        }

        Application.backgroundLoadingPriority = ThreadPriority.Normal;
    }

    private IEnumerator UnloadSceneInternal(string sceneName, bool showLoadingScreen)
    {
        Application.backgroundLoadingPriority = ThreadPriority.Low;

        if (showLoadingScreen)
        {
            UIManager.Instance.ShowLoadingScreen();
        }

        yield return new WaitForSeconds(delayTime);

        AsyncOperation asyncOperation = null;

        Scene scene = SceneManager.GetSceneByName(sceneName);
        if (scene.buildIndex == currentSceneBuildIndex)
        {
            currentSceneBuildIndex = -1;
        }

        // Unload current scene (build index 0 is reserved for core and cannot be unloaded)
        asyncOperation = SceneManager.UnloadSceneAsync(scene);
        while (!asyncOperation.isDone) yield return null;

        yield return new WaitForSeconds(delayTime);

        if (showLoadingScreen)
        {
            UIManager.Instance.HideLoadingScreen();
        }

        Application.backgroundLoadingPriority = ThreadPriority.Normal;
    }
}
