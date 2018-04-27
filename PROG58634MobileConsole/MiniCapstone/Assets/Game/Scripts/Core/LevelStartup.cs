using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LevelStartup : MonoBehaviour
{

    [Header("UI")]
    public string startupMenu;
    public List<UIMenu> menusInLevel = new List<UIMenu>();

    // Use this for initialization
    void Start()
    {
        Debug.Assert(!string.IsNullOrEmpty(startupMenu), "Cannot set startupMenu without a valid UIMenu");
        foreach (UIMenu menu in menusInLevel)
        {
            menu.gameObject.SetActive(false);
        }
        if (menusInLevel.Count > 0)
        {
            Debug.Log("Adding Menus from level to UIManager");
            UIManager.Instance.AddRange(menusInLevel.ToArray());
        }

        UIManager.Instance.HideAll();
        UIManager.Instance.ShowMenu(startupMenu);
    }

    private void OnDestroy()
    {
        // TODO: remove ui menus when leaving level.
    }
}
