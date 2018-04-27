using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner.Runtime;
using BehaviorDesigner.Runtime.Tasks;

public class PunDestroyGameObject : Action
{
    public SharedGameObject toDestroy;

    public override TaskStatus OnUpdate()
    {
        if (toDestroy == null || toDestroy.Value == null)
        {
            PhotonNetwork.Destroy(gameObject);
        }
        else
        {
            //toDestroy.Value.SetActive(false); // Temp til destroy works
            PhotonNetwork.Destroy(toDestroy.Value);
        }

        return TaskStatus.Success;
    }
}
