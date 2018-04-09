using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public abstract class Augment {

    public AugmentBoard board = null;
    public bool needsToBeAdded = true;
    
    public float timer = 0.0f;
    public float duration = 0.0f;

    /// <summary>
    /// Override this to allow interaction with curently applied augments.
    /// </summary>
    public virtual void OnInteraction(Augment other) { }

    /// <summary>
    /// Override this to perform an action when applied. 
    /// Occurs after interacting with currently applied augments.
    /// </summary>
    public virtual void OnApply() { }

    /// <summary>
    /// Override this to perform some action every frame.
    /// </summary>
    public virtual void OnUpdate() { }

    /// <summary>
    /// Override to perform an action when this augment naturally expires
    /// </summary>
    public virtual void OnFinish() { }
}
