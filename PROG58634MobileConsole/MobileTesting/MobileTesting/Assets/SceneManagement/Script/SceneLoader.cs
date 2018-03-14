using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneLoader : MonoBehaviour {

    // singelton

    public GameObject loadingCanvas;

    public string currentScene = "";

    public float delayTime = 1.0f;

    public void LoadScene(string sceneName, bool showLoadingScreen = true, bool unloadCurrentScene = false, string unloadScene = "") {

        //StartCoroutine(LoadSceneInternal(sceneName, showLoadingScreen, unloadCurrentScene, unloadScene));
    }

    private IEnumerable LoadSceneInternal(string sceneName, bool unloadCurrentScene, bool showLoadingScreen, string unloadScene) {

        Application.backgroundLoadingPriority = ThreadPriority.Low;

        if (showLoadingScreen) {

            loadingCanvas.SetActive(true);
        }

        yield return new WaitForSeconds(delayTime);

        AsyncOperation asyncOperation = null;

        // Unload current scene
        if (string.Compare(currentScene, "") != 0) {

            asyncOperation = SceneManager.UnloadSceneAsync(currentScene);

            while (!asyncOperation.isDone) yield return null;
        }

        // Unload the unload scene passed in
        Scene scene = SceneManager.GetSceneByName(unloadScene);

        if (scene != null && scene.isLoaded) {

            asyncOperation = SceneManager.UnloadSceneAsync(scene);

            while (!asyncOperation.isDone) yield return null;
        }

        // load new scene
        asyncOperation = SceneManager.LoadSceneAsync(sceneName, LoadSceneMode.Additive);

        while (!asyncOperation.isDone) yield return null;

        scene = SceneManager.GetSceneByName(sceneName);
        SceneManager.SetActiveScene(scene);

        // Return state back
        if (showLoadingScreen) {

            loadingCanvas.SetActive(false);
        }

        Application.backgroundLoadingPriority = ThreadPriority.Normal;
    }
}
