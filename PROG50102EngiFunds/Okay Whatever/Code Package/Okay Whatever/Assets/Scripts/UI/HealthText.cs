using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class HealthText : MonoBehaviour
{

    private TextMeshProUGUI text;

    public void UpdateHealth(int score)
    {
        if (text == null)
        {
            text = GetComponent<TextMeshProUGUI>();
        }
        Debug.Assert(text != null, "Health Text does not have a reference to text component");
        text.SetText("Health: " + score);
    }
}
