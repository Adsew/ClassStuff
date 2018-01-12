using UnityEngine;

public class IsUIPanel : MonoBehaviour
{
    [SerializeField]
    private int _id;
    public int ID { get { return _id; } }

    public enum eUIPanelState
    {
        invalid = -1,
        off,
        on
    }

    public eUIPanelState state;
}
