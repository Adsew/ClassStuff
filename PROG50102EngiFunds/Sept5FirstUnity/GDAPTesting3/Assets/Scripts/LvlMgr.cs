using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement; // NEED THIS

// similar to ui manager just for scenes

public class LvlMgr : MonoBehaviour {

    public static LvlMgr Instance;

    public List<string> Levels;
    public Scene GlobalScene;   // public for debug
    public Scene CurrentScene;  // current gameplay scene

	// Use this for initialization
	void Start () {
		

        if (Instance == null) {

            Instance = this;
        }

        // Hookup delagates so hey are called when events are fired
        SceneManager.sceneLoaded += OnSceneLoad;
        SceneManager.sceneUnloaded += OnSceneUnloaded;

        // Keep for later used, used often
        GlobalScene = SceneManager.GetSceneByName("Global");
	}
	
    public void LvlMgrUpdate() {


    }

    public void LoadLevel(string name) {
        
        SceneManager.LoadScene(name, LoadSceneMode.Additive);

        // when done wait for on scene load event
    }

    public void UnloadLevel() {

        SceneManager.UnloadSceneAsync(CurrentScene); // Scene will be removed, delagate event fired when done
    }

    public void OnSceneLoad(Scene scene, LoadSceneMode mode) {

        Debug.Log("LvlMgr::SceneLoaded - " + scene.ToString());
        
        // Update reference to currently loaded scene now  that is finished loading.
        CurrentScene = scene;

        // Ensure new GO are added to new scene, not the prev one.
        SceneManager.SetActiveScene(CurrentScene);

        // In game panel
        UIMgr.Instance.SetPanelID(3);
    }

    public void OnSceneUnloaded(Scene scene) {

        Debug.Log("LvlMgr::SceneUnloaded - " + scene.ToString());

        // when gamplay scene is unloded make gloabal current
        SceneManager.SetActiveScene(GlobalScene);

        UIMgr.Instance.SetPanelID(2);
    }

	// Update is called once per frame
	void Update () {

        LvlMgrUpdate();
	}
}
