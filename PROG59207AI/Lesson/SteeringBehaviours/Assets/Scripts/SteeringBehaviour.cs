using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SteeringBehaviour : MonoBehaviour 
{
	public enum SummingMethod
	{
		WeightAverage,
		Prioritized,
		Dithered
	};

	public SummingMethod summingMethod = SteeringBehaviour.SummingMethod.WeightAverage;
	public float Mass = 1.0f;
	public float MaxSpeed = 1.0f;
	public float MaxForce = 10.0f;
	public float SlowRadius = 25.0f;
	public Vector3 Velocity = Vector2.zero;
	public float BoundingRadius = 25.0f;

	private List<SteeringBehaviourBase> steeringBehaviours = new List<SteeringBehaviourBase>();

	private Vector3 steeringForce = Vector3.zero;

	public bool changeRotation = true;
	public bool checkScreenWrap = true;

	public bool reachedGoal = false;

	void Start () 
	{
		steeringBehaviours.AddRange(GetComponentsInParent<SteeringBehaviourBase>());
		foreach(SteeringBehaviourBase behaviour in steeringBehaviours)
		{
			behaviour.steeringComponent = this;
		}
	}
	
	void Update () 
	{
		steeringForce = calculateSteeringForce();

		if (reachedGoal)
		{
			Velocity = Vector3.zero;
		}
		else
		{
			Vector3 acceleration = steeringForce * (1.0f / Mass);

			Velocity = Velocity + (acceleration * Time.deltaTime);

			Velocity = Vector3.ClampMagnitude(Velocity, MaxSpeed);

			Vector3 position = gameObject.transform.position + (Velocity * Time.deltaTime);
			gameObject.transform.position = position;
		}

		if (Velocity.magnitude > 0 && changeRotation)
		{
			// rotate in direction of the velocity
			var angle = Mathf.Atan2(Velocity.y, Velocity.x) * Mathf.Rad2Deg;
			gameObject.transform.rotation = Quaternion.Euler(0, 0, angle);
		}

		if (checkScreenWrap)
		{
			screenWrap();
		}
	}

	Vector3 calculateSteeringForce()
	{
		Vector3 totalForce = Vector3.zero;

		foreach(SteeringBehaviourBase behaviour in steeringBehaviours)
		{
			if (behaviour.enabled == true)
			{
				switch(summingMethod)
				{
					case SummingMethod.WeightAverage:
						totalForce = totalForce + (behaviour.calculateForce() * behaviour.Weight);
						totalForce = Vector3.ClampMagnitude(totalForce, MaxForce);
						break;

					case SummingMethod.Prioritized:
						{
							Vector3 steeringForce = behaviour.calculateForce() * behaviour.Weight;
							if (!AccumlateForce(totalForce, steeringForce))
							{
								return totalForce;
							}
						}
						break;

					case SummingMethod.Dithered:
						break;
				}
			}
		}

		return totalForce;
	}

	bool AccumlateForce(Vector3 runningTotal, Vector3 forceToAdd)
	{
		float magnitudeSoFar = runningTotal.magnitude;
		float magnitudeRemaining = MaxForce - magnitudeSoFar;

		if (magnitudeRemaining <= 0.0f)
		{
			return false;
		}

		float magnitudeToAdd = forceToAdd.magnitude;

		if (magnitudeToAdd < magnitudeRemaining)
		{
			runningTotal = runningTotal + forceToAdd;
		}
		else
		{
			runningTotal = runningTotal + (forceToAdd.normalized * magnitudeRemaining);
		}

		return true;
	}

	void screenWrap()
	{
		var viewportPosition = Camera.main.WorldToViewportPoint(gameObject.transform.position);
		var newPosition = gameObject.transform.position;

		if (viewportPosition.x > 1 || viewportPosition.x < 0)
		{
			newPosition.x = -newPosition.x;
		}

		if (viewportPosition.y > 1 || viewportPosition.y < 0)
		{
			newPosition.y = -newPosition.y;
		}

		gameObject.transform.position = newPosition;
	}
}
