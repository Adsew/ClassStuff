using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class MonoEvent : MonoBehaviour
{
    public enum MonoEventType
    {
        None,
        Start,
        Update,
        CollisionEnter,
        CollisionEnter2D,
        TriggerEnter,
        TriggerEnter2D
    }

    public MonoEventType type;
    public UnityEvent events;

    private void Start()
    {
        FireEvents(MonoEventType.Start);
    }

    private void Update()
    {
        FireEvents(MonoEventType.Update);
    }

    private void OnCollisionEnter(Collision collision)
    {
        FireEvents(MonoEventType.CollisionEnter);
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        FireEvents(MonoEventType.CollisionEnter2D);
    }

    private void OnTriggerEnter(Collider other)
    {
        FireEvents(MonoEventType.TriggerEnter);
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        FireEvents(MonoEventType.TriggerEnter2D);
    }

    private void FireEvents(MonoEventType monoType)
    {
        if (type == monoType)
        {
            if (events != null)
            {
                events.Invoke();
            }
        }
    }
}
