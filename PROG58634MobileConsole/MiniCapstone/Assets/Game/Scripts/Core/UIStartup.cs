using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class UIStartup : MonoBehaviour
{

    public UIMenu startupMenu;
    public List<UIMenu> sceneMenus = new List<UIMenu>();

    private void Awake()
    {
        Debug.Assert(startupMenu != null, "Cannot set Startup Menu with null!");

        foreach (UIMenu menu in sceneMenus)
        {
            menu.gameObject.SetActive(false);
        }

        //UIManager.Instance.HideAll();
        UIManager.Instance.AddRange(sceneMenus.ToArray());

        UIManager.Instance.ShowMenu(startupMenu.menuName);
    }
}
