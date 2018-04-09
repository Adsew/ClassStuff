using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ArriveSteeringBehaviour : SeekSteeringBehaviour 
{
	public float SlowDownDistance = 2.0f;
	public float StopDistance = 0.01f;
	public float DecelerationTweaker = 2.5f;

	public override Vector3 calculateForce()
	{
		checkMouseInput();

		Vector3 toTarget = Target - gameObject.transform.position;
		float distanceToTarget = toTarget.magnitude;

		steeringComponent.reachedGoal = false;

		if (distanceToTarget > SlowDownDistance)
		{
			return base.calculateForce();
		}
		else if (distanceToTarget <= SlowDownDistance && distanceToTarget > StopDistance)
		{
			toTarget.Normalize();

			float speed = distanceToTarget / DecelerationTweaker;
			speed = ((speed < steeringComponent.MaxSpeed) ? speed : steeringComponent.MaxSpeed);

			Vector3 desiredVelocity = toTarget * (speed / distanceToTarget);
			return desiredVelocity - steeringComponent.Velocity;
		}
		else
		{
			steeringComponent.reachedGoal = true;
		}

		return Vector3.zero;
	}
}
