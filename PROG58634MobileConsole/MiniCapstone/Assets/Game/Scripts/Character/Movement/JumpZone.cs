using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JumpZone : MonoBehaviour
{
    public enum ZoneMethod
    {
        None,
        Up,
        Down
    }
    public ZoneMethod method;

    public float yEnd = 0.0f;
    public float xEnd = 0.0f;
    public float yHeight = 0.0f;
    public Track endTrack;

    private void OnTriggerEnter(Collider other)
    {
        Movement movement = other.GetComponent<Movement>();
        if (movement != null)
        {
            movement.SetJumpZone(this);
        }
    }

    private void OnTriggerExit(Collider other)
    {
        Movement movement = other.GetComponent<Movement>();
        if (movement != null)
        {

            movement.RemoveJumpZone(this);
        }
    }

    public Vector3 GetPosition(Vector3 position, float currentTime, float maxDuration)
    {
        float normTime = currentTime / maxDuration;

        float yOffset = yHeight * 4.0f * (normTime - normTime * normTime);

        Vector3 start = new Vector3(transform.position.x, transform.position.y, position.z);
        Vector3 end = new Vector3(xEnd, yEnd, position.z);

        return Vector3.Lerp(start, end, normTime) + yOffset * Vector3.up;
    }

#if UNITY_EDITOR
    public Color lineColor = Color.green;
    private void OnDrawGizmos()
    {
        Gizmos.color = lineColor;

        float normTime = 0.0f;

        Vector3 currPosition = transform.position;
        while (normTime < 1.0f)
        {
            normTime += 0.03f;
            if (normTime > 1.0f)
            {
                normTime = 1.0f;
            }

            Vector3 nextPos = GetPosition(transform.position, normTime, 1.0f);
            Gizmos.DrawLine(currPosition, nextPos);

            currPosition = nextPos;
        }
    }
#endif
}