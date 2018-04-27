using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner.Runtime;
using BehaviorDesigner.Runtime.Tasks;

public class SetTargetFromList : Action
{
    public SharedGameObjectList list;
    public SharedGameObject target;
    public enum TargetSelection
    {
        First,
        Last,
        Closest,
        Farthest
    }
    public TargetSelection selection;

    public override TaskStatus OnUpdate()
    {
        if (list.Value.Count > 0)
        {
            switch (selection)
            {
                case TargetSelection.First:
                    {
                        target = list.Value[0];
                        break;
                    }
                case TargetSelection.Last:
                    {
                        target = list.Value[list.Value.Count - 1];
                        break;
                    }
                case TargetSelection.Closest:
                    {
                        GameObject go = null;
                        float distance = float.MaxValue;

                        foreach (GameObject listGo in list.Value)
                        {
                            float listGoDistance = Vector3.Distance(transform.position, listGo.transform.position);
                            if (listGoDistance < distance)
                            {
                                go = listGo;
                                distance = listGoDistance;
                            }
                        }

                        target.Value = go;
                        break;
                    }
                case TargetSelection.Farthest:
                    {
                        GameObject go = null;
                        float distance = float.MinValue;

                        foreach (GameObject listGo in list.Value)
                        {
                            float listGoDistance = Vector3.Distance(transform.position, listGo.transform.position);
                            if (listGoDistance > distance)
                            {
                                go = listGo;
                                distance = listGoDistance;
                            }
                        }

                        target = go;
                        break;
                    }
            }
        }
        return TaskStatus.Success;
    }
}
