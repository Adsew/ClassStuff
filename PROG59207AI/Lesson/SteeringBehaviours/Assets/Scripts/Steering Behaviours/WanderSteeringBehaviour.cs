using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WanderSteeringBehaviour : SteeringBehaviourBase
{
	public float WanderDistance = 2.0f;
	public float WanderRadius = 1.0f;
	public float WanderJitter = 20.0f;

	private Vector3 WanderTarget;

	private void Start()
	{
		float theta = (float)Random.value * Mathf.PI * 2;
		WanderTarget = new Vector3(WanderRadius * (float)Mathf.Cos(theta), WanderRadius * (float)Mathf.Sin(theta));
	}

	public override Vector3 calculateForce()
	{
		float jitterThisTimeSlice = WanderJitter * Time.deltaTime;

		WanderTarget = WanderTarget + new Vector3(Random.Range(-1.0f, 1.0f) * jitterThisTimeSlice,
												  Random.Range(-1.0f, 1.0f) * jitterThisTimeSlice,
												  0.0f);
		WanderTarget.Normalize();
		WanderTarget = WanderTarget * WanderRadius;

		Target = WanderTarget + new Vector3(WanderDistance, 0, 0);
		Target = gameObject.transform.rotation * Target + gameObject.transform.position;

		Vector3 wanderForce = Target - gameObject.transform.position;
		wanderForce.Normalize();
		wanderForce = wanderForce * steeringComponent.MaxSpeed;

		return wanderForce;
	}

	private void OnDrawGizmos()
	{
		if (debugDraw && steeringComponent != null)
		{
			DebugExtension.DrawArrow(gameObject.transform.position, steeringComponent.Velocity.normalized, Color.red);
			Vector3 circleCenter = gameObject.transform.rotation * new Vector3(WanderDistance, 0, 0)
								   + gameObject.transform.position;
			DebugExtension.DrawCircle(circleCenter, new Vector3(0, 0, 1), Color.white, WanderRadius);
			Debug.DrawLine(gameObject.transform.position, Target, Color.blue);
		}
	}
}
