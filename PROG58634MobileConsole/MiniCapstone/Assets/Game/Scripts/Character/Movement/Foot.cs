using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Foot : MonoBehaviour {

    [Range(0.0f, 10.0f)]
    public float range = 0.5f;

    public Color debugLine = Color.cyan;

	// Use this for initialization
	//void Start () {

 //       Collider myBox = GetComponent<Collider>();
        
 //       if (myBox != null)
 //       {
 //           offset = myBox.bounds.extents.y;
 //       }
	//}
	
	public bool Grounded()
    {
        return Physics.Raycast(transform.position + (Vector3.up * 0.1f), -Vector3.up, range);
    }

    private void OnDrawGizmos()
    {
        Gizmos.color = Color.blue;
        Gizmos.DrawLine(transform.position, transform.position - (Vector3.up * range));
    }
}
