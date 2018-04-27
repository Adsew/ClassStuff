using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class LevelPicker : MonoBehaviour
{
    public Image levelImage;
    public Text levelName;

    [SerializeField]
    private List<Level> levels = new List<Level>();
    private int currentIndex;

    private void OnEnable()
    {
        currentIndex = 0;
        UpdateLevel();
    }

    public void Left()
    {
        currentIndex--;
        if (currentIndex < 0)
        {
            currentIndex = levels.Count - 1;
        }

        UpdateLevel();
    }

    public void Right()
    {
        currentIndex++;
        if (currentIndex > levels.Count - 1)
        {
            currentIndex = 0;
        }

        UpdateLevel();
    }

    public Level GetCurrentLevel()
    {
        if (currentIndex < 0 && currentIndex >= levels.Count)
        {
            return null;
        }

        return levels[currentIndex];
    }

    private void UpdateLevel()
    {
        if (currentIndex < 0 && currentIndex >= levels.Count)
        {
            return;
        }

        if (levelName == null)
        {
            throw new System.NullReferenceException("Cannot update LevelName without a valid reference");
        }

        if (levelImage == null)
        {
            throw new System.NullReferenceException("Cannot update LevelImage witout a valid reference");
        }

        Level level = levels[currentIndex];

        levelName.text = level.levelName;
        levelImage.sprite = level.image;

        LobbyManager.Instance.SelectedLevel = level;
    }
}
