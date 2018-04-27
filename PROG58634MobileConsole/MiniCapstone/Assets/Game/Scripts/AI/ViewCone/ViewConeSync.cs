using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner.Runtime;
using System;

public class ViewConeSync : MonoBehaviour
{
    public BehaviorTree tree;
    private static string treeConeObjectsName = "viewConeObjects";
    public EventBehaviour eventBehaviour;

    public void OnEnable()
    {
        if (eventBehaviour == null)
        {
            throw new NullReferenceException("Cannot listen to EventBehaviour without a valid EventBehaviour.");
        }
        eventBehaviour.Handler.AddListener<ViewConeEvent>(OnViewConeEvent);
    }

    public void OnDisable()
    {
        if (eventBehaviour == null)
        {
            throw new NullReferenceException("Cannot listen to EventBehaviour without a valid EventBehaviour.");
        }

        eventBehaviour.Handler.RemoveListener<ViewConeEvent>(OnViewConeEvent);
    }

    private void OnViewConeEvent(ViewConeEvent coneEvent)
    {
        if (coneEvent == null)
        {
            throw new ArgumentNullException("coneEvent");
        }
        if (tree != null)
        {
            switch (coneEvent.Type)
            {
                case ViewConeEvent.EventType.Stay:
                    {
                        SharedGameObjectList objects = tree.GetVariable(treeConeObjectsName) as SharedGameObjectList;
                        if (!objects.Value.Contains(coneEvent.ConeGameObject))
                        {
                            objects.Value.Add(coneEvent.ConeGameObject);
                        }
                        break;
                    }
                case ViewConeEvent.EventType.Exit:
                    {
                        SharedGameObjectList objects = tree.GetVariable(treeConeObjectsName) as SharedGameObjectList;
                        objects.Value.Remove(coneEvent.ConeGameObject);
                        break;
                    }
                case ViewConeEvent.EventType.Error:
                    {
                        Debug.LogError("ViewConeEvent not handled: Error found!");
                        break;
                    }

            }
        }
    }
}
