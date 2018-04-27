using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AttackEvent : EventHandler.Event
{
    public GameObject attackGameObject;

    public override void Reset()
    {
        attackGameObject = null;
    }
}
