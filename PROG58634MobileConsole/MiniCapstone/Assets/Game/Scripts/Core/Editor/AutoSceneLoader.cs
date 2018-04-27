using UnityEditor;
using UnityEditor.SceneManagement;
using UnityEngine;

// reference: http://wiki.unity3d.com/index.php/SceneAutoLoader
// reference: https://answers.unity.com/questions/362862/menu-items-as-checkboxesradio-buttons.html

[InitializeOnLoad]
public static class AutoSceneLoader
{
    private const string MENU_PATH = "Edit/Project Settings/Auto Load Core";
    private const string MENU_CORE_PATH = "Edit/Project Settings/Select Core Scene";

    private const string editorPrefLoadCore = "AutoSceneLoader.LoadCoreOnPlay";
    private const string editorPrefCoreScene = "AutoSceneLoader.CoreScene";
    private const string editorPrefCurrentScene = "AutoSceneLoader.CurrentScene";

    private static bool LoadCodeOnPlay
    {
        get { return EditorPrefs.GetBool(editorPrefLoadCore, false); }
        set { EditorPrefs.SetBool(editorPrefLoadCore, value); }
    }
    private static string CoreScene
    {
        get { return EditorPrefs.GetString(editorPrefCoreScene, "Core.Unity"); }
        set { EditorPrefs.SetString(editorPrefCoreScene, value); }
    }
    private static string CurrentScene
    {
        get { return EditorPrefs.GetString(editorPrefCurrentScene, EditorSceneManager.GetActiveScene().path); }
        set { EditorPrefs.SetString(editorPrefCurrentScene, value); }
    }

    /*********************************************/
    //  MENU ITEMS (Select and Enable)
    /*********************************************/
    [MenuItem(MENU_CORE_PATH)]
    private static void SelectCoreScene()
    {
        string coreScene = EditorUtility.OpenFilePanel("Select Core Scene", Application.dataPath, "unity");
        coreScene = coreScene.Replace(Application.dataPath, "Assets"); // project relative for scenes
        if (!string.IsNullOrEmpty(coreScene))
        {
            CoreScene = coreScene;
            LoadCodeOnPlay = true;
        }
    }

    // work around that does not properly update checkmark on re-compilation
    [MenuItem(MENU_PATH, true)]
    private static bool ValidateLoadCoreOnPlay()
    {
        ToggleMenuItem(LoadCodeOnPlay);
        return true;
    }

    [MenuItem(MENU_PATH)]
    private static void EnableLoadCoreOnPlay()
    {
        ToggleMenuItem(!LoadCodeOnPlay);
    }

    /// <summary>
    /// Toggle if we want to enable/disable auto load core
    /// </summary>
    private static void ToggleMenuItem(bool enabled)
    {
        //Debug.LogFormat("toggle menu item before set: {0}", enabled);
        LoadCodeOnPlay = enabled;
        //Debug.LogFormat("enable core on play: {0}", LoadCodeOnPlay);
        Menu.SetChecked(MENU_PATH, !enabled);
        Menu.SetChecked(MENU_PATH, enabled);

    }

    static AutoSceneLoader()
    {
        EditorApplication.playModeStateChanged += OnPlayChanged;

        // wait until editor inspectors are updated first
        EditorApplication.delayCall += () =>
        {
            //Debug.Log("Toggle");
            ToggleMenuItem(LoadCodeOnPlay);
        };
    }


    private static void OnPlayChanged(PlayModeStateChange state)
    {
        // if we dont want to load core then no need to execute function
        if (!LoadCodeOnPlay)
        {
            return;
        }

        // if entering play mode then open core scenes
        if (state == PlayModeStateChange.ExitingEditMode)
        {
            CurrentScene = EditorSceneManager.GetActiveScene().path;
            if (EditorSceneManager.SaveCurrentModifiedScenesIfUserWantsTo())
            {
                try
                {
                    EditorSceneManager.OpenScene(CoreScene);
                }
                catch
                {
                    Debug.LogErrorFormat("scene not found: {0}", CoreScene);
                    EditorApplication.isPlaying = false;
                }
            }
        }
        // if exiting playing then switch back to previous scene
        if (state == PlayModeStateChange.EnteredEditMode)
        {
            try
            {
                EditorSceneManager.OpenScene(CurrentScene);
            }
            catch
            {
                Debug.LogErrorFormat("scene not found: {0}", CurrentScene);
            }
        }
    }
}
