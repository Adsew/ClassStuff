using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class SteeringBehaviourBase : MonoBehaviour 
{
	public bool debugDraw = false;

	public float Weight = 1.0f;
	public Vector3 Target = Vector3.zero;
	public bool UseMouseInput = false;

	[HideInInspector]
	public SteeringBehaviour steeringComponent;

	public abstract Vector3 calculateForce();

	protected void checkMouseInput()
	{
		if (Input.GetMouseButtonDown(0) && UseMouseInput)
		{
			Target = Input.mousePosition;
			Target = Camera.main.ScreenToWorldPoint(Target);
			Target.z = 0.0f;
		}
	}
}
