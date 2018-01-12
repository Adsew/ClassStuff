using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CatmullRom
{

    //CatmullRom Calculus
    public static Vector3 getPosition(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, float t)
    {
        return p1 * (-0.5f * t * t * t + t * t - 0.5f * t) +
                p2 * (1.5f * t * t * t + -2.5f * t * t + 1.0f) +
                p3 * (-1.5f * t * t * t + 2.0f * t * t + 0.5f * t) +
                p4 * (0.5f * t * t * t - 0.5f * t * t);
    }


    //CatmullRom tangent
    public static Vector3 getTangent(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, float t)
    {
        return t * t * 3 * (-0.5f * p1 + 1.5f * p2 - 1.5f * p3 + 0.5f * p4) +
                t * 2 * (p1 - 2.5f * p2 + 2.0f * p3 - 0.5f * p4) +
                -0.5f * p1 + 0.5f * p3;
    }
}
