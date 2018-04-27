using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using System;

// reference: https://gist.github.com/stfx/3786466, http://www.willrmiller.com/?p=87

public class EventHandler
{
    public class Event
    {
        public virtual void Reset() { }
    }

    public delegate void EventDelegate<T>(T e) where T : Event;

    private readonly Dictionary<Type, Delegate> listeners = new Dictionary<Type, Delegate>();

    public void AddListener<T>(EventDelegate<T> _delegate) where T : Event
    {
        Delegate del;
        if (listeners.TryGetValue(typeof(T), out del))
        {
            // combine the current delegate for typeof(T) and the new listener
            listeners[typeof(T)] = Delegate.Combine(del, _delegate);
        }
        else
        {
            // if there is currently no listeners set the delegate to the new listener
            listeners[typeof(T)] = _delegate;
        }
    }

    public void RemoveListener<T>(EventDelegate<T> _delegate) where T : Event
    {
        // check if there are registered listeners 
        Delegate del;
        if (listeners.TryGetValue(typeof(T), out del))
        {
            // remove listener from list
            Delegate newDel = Delegate.Remove(del, _delegate);

            // remove completely if there are zero listeneres for typeof(T)
            if (newDel == null)
            {
                listeners.Remove(typeof(T));
            }
            else
            {
                // otherwise set listener to new delegate
                listeners[typeof(T)] = newDel;
            }
        }
    }

    public void Invoke<T>(T e) where T : Event
    {
        if (e == null)
        {
            throw new ArgumentNullException("Cannot Invoke a null Event");
        }


        Delegate del;
        // check if listeners are present for typeof(T)
        if (listeners.TryGetValue(typeof(T), out del))
        {
            // cast delegate to desired delegate callback
            EventDelegate<T> callback = del as EventDelegate<T>;
            if (callback == null)
            {
                throw new NullReferenceException("Cannot invoke on an event type that was not previously registered as a listener.");
            }

            // invoke callback
            callback(e);
        }
    }
}
