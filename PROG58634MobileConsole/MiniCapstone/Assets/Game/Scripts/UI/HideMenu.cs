using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HideMenu : MonoBehaviour
{
    public UIMenu uIMenu;

    public void Execute()
    {
        UIManager.Instance.HideMenu(uIMenu);
    }
}
