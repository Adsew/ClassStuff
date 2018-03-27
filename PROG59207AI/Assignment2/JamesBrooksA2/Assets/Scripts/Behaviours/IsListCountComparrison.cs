using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner.Runtime;
using BehaviorDesigner.Runtime.Tasks;

public class IsListCountComparrison : Conditional {

    public SharedObjectList list;
    public SharedInt integer;

    public enum Comparitor {

        Equals,
        GreaterThan,
        GreaterThanEquals,
        LessThan,
        LessThanEquals
    }

    public Comparitor compareMethod = Comparitor.Equals;

    public override TaskStatus OnUpdate() {

        if (list != null) {

            if (compareMethod == Comparitor.Equals && list.Value.Count == integer.Value) {

                return TaskStatus.Success;
            }
            else if (compareMethod == Comparitor.GreaterThan && list.Value.Count > integer.Value) {

                return TaskStatus.Success;
            }
            else if (compareMethod == Comparitor.GreaterThanEquals && list.Value.Count >= integer.Value) {

                return TaskStatus.Success;
            }
            else if (compareMethod == Comparitor.LessThan && list.Value.Count < integer.Value) {

                return TaskStatus.Success;
            }
            else if (compareMethod == Comparitor.LessThanEquals && list.Value.Count <= integer.Value) {

                return TaskStatus.Success;
            }
        }

        return TaskStatus.Failure;
    }
}
