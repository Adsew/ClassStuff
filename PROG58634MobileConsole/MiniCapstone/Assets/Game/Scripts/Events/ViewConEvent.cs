using UnityEngine;
using System.Collections;

public class ViewConeEvent : EventHandler.Event
{
    public GameObject ConeGameObject { get; private set; }
    public enum EventType
    {
        Error,
        Stay,
        Enter,
        Exit
    }
    public EventType Type { get; private set; }

    public void OnStay(GameObject interestingObject)
    {
        Reset();
        ConeGameObject = interestingObject;
        Type = EventType.Stay;
    }

    public void OnEnter(GameObject interestingObject)
    {
        Reset();
        ConeGameObject = interestingObject;
        Type = EventType.Enter;
    }

    public void OnExit(GameObject interestingObject)
    {
        Reset();
        ConeGameObject = interestingObject;
        Type = EventType.Exit;
    }

    public override void Reset()
    {
        ConeGameObject = null;
        Type = EventType.Error;
    }
}
