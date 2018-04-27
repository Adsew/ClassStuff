using UnityEngine;
using System.Collections;

public class EventBehaviour : MonoBehaviour
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
