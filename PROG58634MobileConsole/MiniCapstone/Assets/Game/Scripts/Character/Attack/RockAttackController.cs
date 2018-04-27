using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner;
using BehaviorDesigner.Runtime;

public struct ParabolicData
{
    public bool IsValid;
    public Vector3 InitialVelocity;
    public float Duration;
}

public class RockAttackController : AttackController
{
    public string bdTargetName;
    public Transform rockStartPosition;
    public float maxHeight = 20;
    public GameObject rockPrefab;

    private BehaviorTree tree = null;

    protected override void Start()
    {
        base.Start();
        tree = GetComponent<BehaviorTree>();
    }

    public override void StartAttack()
    {
        Debug.Log("Attack");
        if (CanAttack)
        {
            if (_animator != null && !string.IsNullOrEmpty(AttackTrigger))
            {
                photonView.RPC("RPC_TriggerThrowRockAnim", PhotonTargets.All);
                StartCoroutine(Attacking());
            }
        }
    }

    [PunRPC]
    protected void RPC_TriggerThrowRockAnim()
    {
        if (_animator != null)
        {
            _animator.SetTrigger(AttackTrigger);
        }
    }

    public override void FinishAttack()
    {
        if (photonView.isMine)
        {
            if (tree == null || rockStartPosition == null)
            {
                throw new System.NullReferenceException("Cannot throw rock without a valid tree and rock prefab");
            }

            var sharedVar = tree.GetVariable(bdTargetName);
            if (sharedVar != null)
            {
                var targetVar = sharedVar as SharedGameObject;
                if (targetVar != null && targetVar.Value != null)
                {
                    photonView.RPC("RPC_ThrowRock", PhotonTargets.All, targetVar.Value.transform.position);
                }
            }
        }
    }

    private ParabolicData CalcInitialVelocity(Vector3 start, Vector3 end)
    {
        // Calculate the displacment
        Vector3 disp = new Vector3
        {
            x = end.x - start.x,
            y = end.y - start.y,
            z = end.z - start.z
        };

        ParabolicData data;
        data.IsValid = true;
        float gravity = Physics.gravity.y;
        data.Duration = (Mathf.Sqrt(-2.0f * maxHeight / gravity) + Mathf.Sqrt(2.0f * (disp.y - maxHeight) / gravity));
        Vector3 vel = new Vector3
        {
            x = disp.x / data.Duration,
            y = Mathf.Sqrt(-2 * gravity * maxHeight),
            z = disp.z / data.Duration
        };

        data.InitialVelocity = vel;

        return data;
    }

    //[PunRPC]
    //public void RPC_ThrowRock()
    //{
    //    if (tree == null || rockStartPosition == null)
    //    {
    //        throw new System.NullReferenceException("Cannot throw rock without a valid tree and rock prefab");
    //    }

    //    var sharedVar = tree.GetVariable(bdTargetName);
    //    if (sharedVar != null)
    //    {
    //        var targetVar = sharedVar as SharedGameObject;
    //        if (targetVar != null && targetVar.Value != null)
    //        {
    //            GameObject go = Instantiate(rockPrefab, rockStartPosition.position, rockStartPosition.rotation);
    //            Rigidbody rb = go.GetComponent<Rigidbody>();

    //            var data = CalcInitialVelocity(rockStartPosition.position, targetVar.Value.transform.position);
    //            if (rb != null)
    //            {
    //                rb.velocity = data.InitialVelocity;
    //            }

    //            Rock rock = go.GetComponent<Rock>();
    //            if (rock != null)
    //            {
    //                rock.attackController = this;
    //                rock.launchData = data;
    //            }
    //        }
    //    }
    //}

    [PunRPC]
    public void RPC_ThrowRock(Vector3 position)
    {
        GameObject go = Instantiate(rockPrefab, position, transform.rotation);
        Rigidbody rb = go.GetComponent<Rigidbody>();

        var data = CalcInitialVelocity(rockStartPosition.position, position);
        if (rb != null)
        {
            rb.velocity = data.InitialVelocity;
        }

        if (!photonView.isMine)
        {
            BoxCollider collider = go.GetComponent<BoxCollider>();
            if (collider != null)
            {
                collider.isTrigger = true;
            }
        }

        Rock rock = go.GetComponent<Rock>();
        if (rock != null)
        {
            rock.attackController = this;
            rock.launchData = data;
        }
    }
}
