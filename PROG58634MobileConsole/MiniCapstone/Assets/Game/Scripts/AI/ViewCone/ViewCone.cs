
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using System;

[ExecuteInEditMode]
public class ViewCone : ViewObject
{
    public float Angle { get { return angle; } set { angle = value; } }
    public float Distance { get { return distance; } set { distance = value; } }

    [SerializeField]
    private float angle;
    [SerializeField]
    private float distance;
    public bool checkWithRaycast = true;
    public EventBehaviour eventBehaviour;
    private ViewConeEvent _coneEvent = new ViewConeEvent();

    private void Start()
    {
        UpdateBoxCollider();
    }

    private void OnTriggerStay(Collider other)
    {
        IInterestingObject interestingObject = other.gameObject.GetComponent(typeof(IInterestingObject)) as IInterestingObject;
        if (interestingObject != null)
        {
            if (InCone(interestingObject, other.transform))
            {
                if (eventBehaviour == null)
                {
                    throw new NullReferenceException("Cannot fire event without EventBehaviour. Unexpected result found!");
                }

                _coneEvent.OnStay(other.gameObject);
                eventBehaviour.Handler.Invoke(_coneEvent);
            }
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        IInterestingObject interestingObject = other.gameObject.GetComponent(typeof(IInterestingObject)) as IInterestingObject;
        if (interestingObject != null)
        {
            if (InCone(interestingObject, other.transform))
            {
                if (eventBehaviour == null)
                {
                    throw new NullReferenceException("Cannot fire event without EventBehaviour. Unexpected result found!");
                }
                _coneEvent.OnEnter(other.gameObject);
                eventBehaviour.Handler.Invoke(_coneEvent);
            }
        }
    }

    private void OnTriggerExit(Collider other)
    {
        IInterestingObject interestingObject = other.gameObject.GetComponent(typeof(IInterestingObject)) as IInterestingObject;
        if (interestingObject != null)
        {
            if (eventBehaviour == null)
            {
                throw new NullReferenceException("Cannot fire event without EventBehaviour. Unexpected result found!");
            }
            _coneEvent.OnExit(other.gameObject);
            eventBehaviour.Handler.Invoke(_coneEvent);
        }
    }

    /// <summary>
    /// Update the Box Collider used for the view cone
    /// </summary>
    public void UpdateBoxCollider()
    {
        BoxCollider boxCollider = GetComponent<BoxCollider>();
        if (boxCollider != null)
        {
            boxCollider.center = new Vector3(0, 0, distance / 2);

            float opposite = Mathf.Tan(Mathf.Deg2Rad * (angle * 0.5f)) * distance;
            opposite = Mathf.Abs(opposite) * 2.0f;

            boxCollider.size = new Vector3(opposite, opposite, distance);
        }
    }

    private bool InCone(IInterestingObject other, Transform otherTransform)
    {
        Vector3 position = otherTransform.position;

        bool result = false;

        float actualAngle = Vector3.Angle(transform.position, position);
        if (actualAngle >= 0.0f && actualAngle <= angle)
        {
            if (Vector3.Distance(transform.position, position) <= distance)
            {
                if (checkWithRaycast)
                {
                    RaycastHit hit;
                    if (Physics.Raycast(transform.position, transform.forward, out hit, distance))
                    {
                        other.OnInsideView(this);
                        result = true;
                    }
                }
                else
                {
                    result = true;
                }
            }
        }

        return result;
    }

#if UNITY_EDITOR
    [Header("Gizmo")]
    [Space(10)]
    public Color coneColor = Color.red;
    public float thetaScale = 0.01f;
    [Header("Center Line")]
    public bool drawCenterLine = false;
    public Color centerConeColor = Color.black;
    [Header("Extra")]
    public bool drawExtraLines = false;
    public Color extraLineColor = Color.red;
    private void OnDrawGizmos()
    {
        Vector3 center = transform.position + transform.forward * distance;
        float radius = Mathf.Tan(Mathf.Deg2Rad * (angle * 0.5f)) * distance;

        if (drawCenterLine)
        {
            // draw center line
            Gizmos.color = centerConeColor;
            Gizmos.DrawLine(transform.position, center);
        }

        Gizmos.color = coneColor;

        // draw right line
        Gizmos.DrawLine(transform.position, center + transform.right * radius);

        // draw left line
        Gizmos.DrawLine(transform.position, center - transform.right * radius);

        if (drawExtraLines)
        {
            Gizmos.color = extraLineColor;
            // draw up line
            Gizmos.DrawLine(transform.position, center + transform.up * radius);

            // draw down line 
            Gizmos.DrawLine(transform.position, center - transform.up * radius);
        }

        // draw circle
        GizmosExtensions.DrawCircle(center, transform.up, transform.right, radius, thetaScale, coneColor);
    }
#endif
}