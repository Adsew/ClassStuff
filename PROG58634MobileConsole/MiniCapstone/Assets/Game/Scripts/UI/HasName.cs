using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Text.RegularExpressions;

public class HasName : MonoBehaviour
{
    public Text textField;
    private Button button;

    // Use this for initialization
    void Start()
    {
        button = GetComponent<Button>();
    }

    // Update is called once per frame
    void Update()
    {
        if (button != null)
        {
            if (textField != null)
            {
                string str = Regex.Replace(textField.text, @"[^0-9a-zA-Z]", "");
                if (string.IsNullOrEmpty(str) || !PhotonNetwork.connected)
                {
                    button.interactable = false;
                }
                else
                {
                    button.interactable = true;
                }
            }
            else
            {
                button.interactable = false;
            }
        }
    }
}
