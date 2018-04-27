using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Startup : MonoBehaviour
{
    public SceneField startupScene;
    public float delayTime = 2.0f;

    private void Start()
    {
        // get the startup scene
        Scene scene = SceneManager.GetSceneByName(startupScene);

        if (!scene.isLoaded)
        {
            // loading of scene is required
            StartCoroutine(LoadStartup());
        }
        else
        {
            // scene is already loaded so just stall
            StartCoroutine(StallStartup());
        }
    }

    IEnumerator LoadStartup()
    {
        UIManager.Instance.ShowLoadingScreen();

        AsyncOperation asyncOperation = SceneManager.LoadSceneAsync(startupScene, LoadSceneMode.Additive);
        while (!asyncOperation.isDone) yield return null;

        Debug.Log("Scene Loaded: " + startupScene);

        yield return new WaitForSeconds(delayTime);

        UIManager.Instance.HideLoadingScreen();

        SceneManager.SetActiveScene(SceneManager.GetSceneByName(startupScene));
    }

    IEnumerator StallStartup()
    {
        UIManager.Instance.ShowLoadingScreen();

        yield return new WaitForSeconds(delayTime);

        UIManager.Instance.HideLoadingScreen();

        SceneManager.SetActiveScene(SceneManager.GetSceneByName(startupScene));
    }
}
