using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EventManager : Singleton<EventManager>
{
    private EventHandler _eventHandler = null;
    public EventHandler Handler
    {
        get
        {
            if (_eventHandler == null)
            {
                _eventHandler = new EventHandler();
            }
            return _eventHandler;
        }
    }
}
