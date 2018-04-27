using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class GizmosExtensions
{
    static float two_pi = Mathf.PI * 2.0f;


    public static void DrawCircle(Vector3 center, Vector3 perp1, Vector3 perp2, float radius, float thetaScale, Color color)
    {
        Gizmos.color = color;



        float prevX = center.x + radius * Mathf.Cos(0.0f) * perp1.x + radius * Mathf.Sin(0.0f) * perp2.x;
        float prevY = center.y + radius * Mathf.Cos(0.0f) * perp1.y + radius * Mathf.Sin(0.0f) * perp2.y;
        float prevZ = center.z + radius * Mathf.Cos(0.0f) * perp1.z + radius * Mathf.Sin(0.0f) * perp2.z;
        Vector3 prev = new Vector3(prevX, prevY, prevZ);
        Vector3 next = Vector3.zero;


        // draw circle
        for (float theta = thetaScale; theta <= two_pi; theta += thetaScale)
        {
            next.x = center.x + radius * Mathf.Cos(theta) * perp1.x + radius * Mathf.Sin(theta) * perp2.x;
            next.y = center.y + radius * Mathf.Cos(theta) * perp1.y + radius * Mathf.Sin(theta) * perp2.y;
            next.z = center.z + radius * Mathf.Cos(theta) * perp1.z + radius * Mathf.Sin(theta) * perp2.z;

            Gizmos.DrawLine(prev, next);

            prev = next;
        }
    }
}