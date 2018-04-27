using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Track : MonoBehaviour
{
    public Transform start;
    public Transform end;

#if UNITY_EDITOR
    public bool draw = true;
    public Color color = Color.red;

    private void OnDrawGizmos()
    {
        if (draw)
        {
            Gizmos.color = color;
            if (start != null && end != null)
            {
                Gizmos.DrawLine(start.position, end.position);
            }
        }
    }
#endif
}