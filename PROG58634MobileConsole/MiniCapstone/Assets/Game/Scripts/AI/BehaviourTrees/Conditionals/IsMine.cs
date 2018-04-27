using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner.Runtime.Tasks;

public class IsMine : Conditional
{
    private PhotonView view;

    public override void OnStart()
    {
        view = GetComponent<PhotonView>();
    }

    public override TaskStatus OnUpdate()
    {
        if (view != null && view.isMine)
        {
            return TaskStatus.Success;
        }
        return TaskStatus.Failure;
    }
}
