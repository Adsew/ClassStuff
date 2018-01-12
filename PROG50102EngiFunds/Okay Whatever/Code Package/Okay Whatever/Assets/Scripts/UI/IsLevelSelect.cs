using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class IsLevelSelect : MonoBehaviour
{

    public GameObject btnPrefab;

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    public void AddButton(string name, int idName)
    {
        Debug.Log("level name: " + name);
        GameObject btn = Instantiate(btnPrefab);
        btn.transform.SetParent(transform, false);

        TextMeshProUGUI text = btn.GetComponentInChildren<TextMeshProUGUI>();
        if (text != null)
        {
            text.SetText(idName.ToString());
        }

        Button button = btn.GetComponent<Button>();
        if (button != null)
        {
            button.onClick.AddListener(delegate { GameStateManager.Instance.GoToInGame(name); });
        }
    }

}
