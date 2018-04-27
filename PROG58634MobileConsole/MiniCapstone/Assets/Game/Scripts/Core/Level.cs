using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New Level", menuName = "Level")]
public class Level : ScriptableObject
{
    public string levelName;
    public Sprite image;
    public SceneField activeScene;
    public List<SceneField> scenes = new List<SceneField>();
}