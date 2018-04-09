using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FleeSteeringBehaviour : SteeringBehaviourBase
{
	public float fleeDistance = 1.0f;
	public Transform EnemyTarget;

	public override Vector3 calculateForce()
	{
		if (EnemyTarget == null)
		{
			checkMouseInput();
		}
		else
		{
			Target = EnemyTarget.position;
		}

		float distance = (Target - gameObject.transform.position).magnitude;
		if (distance > fleeDistance)
		{
			return Vector3.zero;
		}

		Vector3 desiredVelocity = (gameObject.transform.position - Target).normalized;
		desiredVelocity = desiredVelocity * steeringComponent.MaxSpeed;
		return desiredVelocity - steeringComponent.Velocity;
	}

	private void OnDrawGizmos()
	{
		if (debugDraw)
		{
			DebugExtension.DrawCircle(transform.position, new Vector3(0, 0, 1), Color.white, fleeDistance);
		}
	}
}
