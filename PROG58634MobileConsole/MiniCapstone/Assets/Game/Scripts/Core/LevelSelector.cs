using UnityEngine;

public class LevelSelector : MonoBehaviour
{
    public Level level;

    public void LoadLevel()
    {
        Debug.Assert(level != null, "Level must be set to load.");
        LevelLoader.Instance.LoadLevel(level);
    }
}
