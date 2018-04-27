using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class LoadingScreenUIMenu : UIMenu
{
    [TextArea]
    public List<string> messages = new List<string>();
    public Vector2 quoteSpawnRange = new Vector2(400.0f, 400.0f);
    public Vector2Int fontSizeRange = new Vector2Int(10, 18);
    public Vector2 quoteMoveSpeedRange = new Vector2(1.0f, 3.0f);
    public float quoteDespawnTime = 2.0f;
    public float switchTime = 1.5f;
    public GameObject loadingPanel = null;
    public GameObject textPrefab = null;
    
    private string _currentMessage;
    private int index;
    private float _currentElapsed = 0.0f;

    // Update is called once per frame
    void Update()
    {
        _currentElapsed += Time.deltaTime;
        if (_currentElapsed >= switchTime)
        {
            _currentElapsed = 0.0f;
            LoadNextMessage();
        }
    }

    public void LoadNextMessage(bool random = false)
    {
        if (messages != null && messages.Count > 0)
        {
            if (random)
            {
                index = Random.Range(0, messages.Count - 1);
            }
            else
            {
                index++;
                if (index > messages.Count - 1)
                {
                    index = 0;
                }
            }
            _currentMessage = messages[index];
        }
        else
        {
            Debug.Log("Could load custom message. None provided!");
            _currentMessage = "Loading...";
        }

        if (loadingPanel != null && textPrefab != null)
        {
            GameObject newTextObj = Instantiate(textPrefab);

            // Set dynamic text
            Text __text = newTextObj.GetComponent<Text>();

            if (__text != null)
            {
                __text.text = _currentMessage;
                __text.fontSize = Random.Range(fontSizeRange.x, fontSizeRange.y);
            }

            // Set dynamic movement
            Rigidbody2D rb = newTextObj.GetComponent<Rigidbody2D>();

            if (rb != null) {

                rb.velocity = new Vector2(Random.Range(quoteMoveSpeedRange.x, quoteMoveSpeedRange.y), 0.0f);
            }

            // Parent to the loading screen, adjust size for accuracy
            newTextObj.transform.SetParent(loadingPanel.transform);
            newTextObj.transform.localPosition = new Vector3(
                Random.Range(-quoteSpawnRange.x, quoteSpawnRange.x),
                Random.Range(-quoteSpawnRange.y, quoteSpawnRange.y),
                0.0f
                );
            newTextObj.transform.localScale = new Vector3(1.0f, 1.0f, 1.0f);

            Destroy(newTextObj, quoteDespawnTime);
        }
    }
    
    public virtual void OnEnable()
    {
        LoadNextMessage(true);
    }

    private void OnDisable()
    {
        _currentElapsed = 0.0f;
    }
}
