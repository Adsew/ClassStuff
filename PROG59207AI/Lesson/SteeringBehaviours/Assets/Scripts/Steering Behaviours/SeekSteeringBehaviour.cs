using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SeekSteeringBehaviour : SteeringBehaviourBase
{
	public override Vector3 calculateForce()
	{
		checkMouseInput();

		Vector3 desiredVelocity = (Target - gameObject.transform.position).normalized;
		desiredVelocity = desiredVelocity * steeringComponent.MaxSpeed;
		return desiredVelocity - steeringComponent.Velocity;
	}
}
