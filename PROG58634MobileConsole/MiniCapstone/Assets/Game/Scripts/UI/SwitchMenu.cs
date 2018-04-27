using UnityEngine;

public class SwitchMenu : MonoBehaviour
{

    public UIMenu switchTo;
    public string menuName;

    public void Switch()
    {
        if (switchTo != null)
        {
            UIManager.Instance.ShowOnly(switchTo);
        }
        else if (!string.IsNullOrEmpty(menuName))
        {
            UIManager.Instance.ShowOnly(menuName);
        }
        else
        {
            throw new System.Exception("Cannot switch menu without a valid Menu");
        }
    }
}
