using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OffsetPursuitSteeringBehaviour : ArriveSteeringBehaviour {

    public SteeringBehaviour pursuitObject;
    public Vector3 offset;

    public override Vector3 calculateForce()
    {
        if (pursuitObject != null)
        {
            Vector3 worldOffset = (pursuitObject.transform.rotation * offset.normalized) + pursuitObject.transform.position;

            Vector3 toOffset = worldOffset - steeringComponent.transform.position;

            float lookAheadTime = toOffset.magnitude / (steeringComponent.MaxSpeed + pursuitObject.Velocity.magnitude);

            Target = worldOffset + pursuitObject.Velocity * lookAheadTime;

            return base.calculateForce();
        }

        return Vector3.zero;
    }
}
