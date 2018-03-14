using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

[RequireComponent(typeof(OffMeshLink))]
public class JumpCurve : MonoBehaviour {

    public Transform startPos;
    public Transform endPos;

    public float height = 1.0f;


    public Vector3 getPosition(float currentTime, float maximumDuration) {

        if (startPos == null || endPos == null) {

            return Vector3.zero;
        }

        float normalizedTime = currentTime / maximumDuration;
        float yPos = height * 4.0f * (normalizedTime - normalizedTime * normalizedTime);
        
        return Vector3.Lerp(startPos.position, endPos.position, normalizedTime) + yPos * Vector3.up;
    }

    public void OnDrawGizmos() {
        
        if (startPos == null || endPos == null) {

            return;
        }

        Vector3 currentPosition = startPos.position;
        float normalizedTime = 0.0f;

        Gizmos.color = Color.blue;

        while (normalizedTime < 1.0f) {

            normalizedTime += 0.03f;

            if (normalizedTime > 1.0f) {

                normalizedTime = 1.0f;
            }

            Vector3 nextPosition = getPosition(normalizedTime, 1.0f);
            Gizmos.DrawLine(currentPosition, nextPosition);
            currentPosition = nextPosition;
        }
    }
}
