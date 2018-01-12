using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

public class BundleManager : MonoBehaviour
{

    private static BundleManager _instance;
    public static BundleManager Instance
    {
        get { return _instance; }
    }

    void Awake()
    {
        if (_instance == null)
        {
            _instance = this;
        }
        else
        {
            Destroy(this);
        }
    }

    public List<Object> LoadObjectsFromFile(string name)
    {
        var bundle = AssetBundle.LoadFromFile(Path.Combine(Application.dataPath + "/AssetBundles", name));
        if (bundle == null)
        {
            Debug.Log("Failed to load AssetBundle!");
            return new List<Object>();
        }

        return new List<Object>(bundle.LoadAllAssets());
    }

    public List<string> LoadScenes(string name)
    {
        var bundle = AssetBundle.LoadFromFile(Path.Combine(Application.dataPath + "/AssetBundles", name));
        if (bundle == null)
        {
            Debug.Log("Failed to load AssetBundle!");
            return new List<string>();
        }
        return new List<string>(bundle.GetAllScenePaths());
    }

    //public List<string> LoadScenes(string name)
    //{
    //    var bundleRequest = AssetBundle.LoadFromFileAsync(Path.Combine(Application.dataPath + "/AssetBundles", name));
    //    yield return bundleRequest;

    //    var bundle 
    //    if (bundle == null)
    //    {
    //        Debug.Log("Failed to load AssetBundle!");
    //        return new List<string>();
    //    }
    //    return new List<string>(bundle.GetAllScenePaths());
    //}
}
