using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NotifyBarrelReachedEnd : MonoBehaviour
{
    private List<GameObject> mListeners = new List<GameObject>();

    public void OnSplineEnded()
    {
        EnemyManager.Instance.barrelReachedEnd(this.gameObject);
        foreach (GameObject obj in mListeners)
        {
            obj.SendMessage("OnSplineEnded");
        }
    }

    public void registerListenerBarrelReachedEnd(GameObject obj)
    {
        mListeners.Add(obj);
    }
}
