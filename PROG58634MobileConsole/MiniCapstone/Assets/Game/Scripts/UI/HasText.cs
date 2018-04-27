using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HasText : MonoBehaviour
{
    public Button button;

    // Use this for initialization
    void Start()
    {
        button.enabled = false;
    }

    public void UpdateText(string text)
    {
        if (string.IsNullOrEmpty(text))
        {
            button.interactable = false;
        }
        else
        {
            button.interactable = true;
        }
    }
}
