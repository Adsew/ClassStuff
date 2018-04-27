using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class UIManager : Singleton<UIManager>
{
	public EventSystem eventSystem;
    [SerializeField]
    private UIMenu loadingScreen;

    [SerializeField]
    private List<UIMenu> menus = new List<UIMenu>();
    private List<UIMenu> openMenus = new List<UIMenu>();

    public void AddMenu(UIMenu menu)
    {
        if (!menus.Contains(menu))
        {
            menus.Add(menu);
        }
    }

    public void AddRange(UIMenu[] newMenus)
    {
        if (newMenus == null || menus == null)
        {
            Debug.LogError("Cannot add range without valid set of menus");
            return;
        }

        for (int i = 0; i < newMenus.Length; i++)
        {
            if (!menus.Contains(newMenus[i]))
            {
                menus.Add(newMenus[i]);
            }
        }
    }

    public void RemoveMenu(UIMenu menu)
    {
        menus.Remove(menu);
    }

    public void ShowOnly(UIMenu menu)
    {
        HideAll();
        ShowMenu(menu);
    }

    public void ShowOnly(string menuName)
    {
        HideAll();
        ShowMenu(menuName);
    }

    public void ShowMenu(UIMenu menu)
    {
        Debug.Assert(menus != null, "Menu list was found null.");
        if (menu != null)
        {
            UIMenu regMenu = menus.Find(item => item.menuName == menu.menuName);
            if (regMenu == null)
            {
                Debug.LogWarning("ShowMenu should only be called if menu is previously registered!");
                menus.Add(menu);
            }
            //Debug.LogFormat("Showing Menu: {0}", menu.menuName);
            menu.gameObject.SetActive(true);

			if (menu.firstFocus != null)
			{
				menu.firstFocus.Select();
			}


            if (!openMenus.Contains(menu))
            {
                openMenus.Add(menu);
            }
        }
    }

    public void ShowMenu(string name)
    {
        UIMenu menu = menus.Find(item => item.menuName == name);
        if (menu != null)
        {
            //Debug.LogFormat("Showing Menu: {0}", menu.menuName);
            menu.gameObject.SetActive(true);
            openMenus.Add(menu);

			if (menu.firstFocus != null)
			{
				menu.firstFocus.Select();
			}
        }
    }

    public void HideMenu(string name)
    {
        UIMenu menu = menus.Find(item => item.menuName == name);
        if (menu != null)
        {
            //Debug.LogFormat("Hiding Menu: {0}", menu.menuName);
            menu.gameObject.SetActive(false);
            openMenus.Remove(menu);
        }
    }

    public void HideMenu(UIMenu menu)
    {
        if (menu != null)
        {
            UIMenu regMenu = menus.Find(item => item.menuName == menu.menuName);
            if (regMenu == null)
            {
                Debug.LogWarning("HideMenu should only be called if menu is previously registered!");
                menus.Add(menu);
            }

            //Debug.LogFormat("Hiding Menu: {0}", menu.menuName);

            UIMenu openMenu = openMenus.Find(item => item.menuName == menu.menuName);
            if (openMenu != null)
            {
                openMenus.Remove(openMenu);
            }
        }
    }

    public void HideAll()
    {
        //Debug.Log("Hiding all open menus");
        foreach (UIMenu menu in openMenus)
        {
            menu.gameObject.SetActive(false);
        }

        openMenus.Clear();
    }

    public void ShowLoadingScreen()
    {
        foreach (UIMenu menu in openMenus)
        {
            menu.gameObject.SetActive(false);
        }


        if (loadingScreen != null)
        {
            loadingScreen.gameObject.SetActive(true);
        }
    }



    public void HideLoadingScreen()
    {
        //Debug.Log("Showing loading screen");

        foreach (UIMenu menu in openMenus)
        {
            menu.gameObject.SetActive(true);
        }

        if (loadingScreen != null)
        {
            loadingScreen.gameObject.SetActive(false);
        }
    }

    public UIMenu GetUIMenu(string name)
    {
        foreach (UIMenu menu in menus)
        {
            if (menu.menuName == name)
            {
                return menu;
            }
        }

        return null;
    }
}
