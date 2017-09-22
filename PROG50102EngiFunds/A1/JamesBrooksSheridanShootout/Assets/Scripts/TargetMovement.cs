using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TargetMovement : MonoBehaviour {

    [Range(0,1)]
    public float t;

    public List<GameObject> ContPoints;

    public GameObject head;

    void CatmullRomSpline()
    {
        Vector3 newPosition;

        Vector3 p0 = ContPoints[0].transform.position;
        Vector3 p1 = ContPoints[1].transform.position;
        Vector3 p2 = ContPoints[2].transform.position;
        Vector3 p3 = ContPoints[3].transform.position;

        //Catmull rom equation converted
        newPosition = 0.5f * (
            (p1 * 2.0f)
            + (p2 - p0) * t
            + (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t * t
            + (3.0f * p1 - p0 - 3.0f * p2 + p3) * t * t * t
            );

        head.transform.SetPositionAndRotation(newPosition, head.transform.rotation);
    }
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
