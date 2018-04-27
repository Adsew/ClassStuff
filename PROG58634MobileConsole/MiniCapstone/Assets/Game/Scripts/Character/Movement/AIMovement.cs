using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class AIMovement : Photon.PunBehaviour, IPunObservable
{
    public string AnimatorSpeed = "Speed";
    public string JumpTrigger = "Jump";

    public float turningDeadzone = 10.0f;

    public float angularDampeningTime = 5.0f;

    private NavMeshAgent _agent;
    private Animator _animator;

    private float speed = 0.0f;

    private bool jumping = false;
    private bool _canMove = false;
    public bool CanMove
    {
        get { return _canMove; }
        set
        {
            _canMove = value;
            if (_agent != null)
            {
                _agent.isStopped = _canMove;
            }
        }
    }
    public Color debugDestLine = Color.cyan;

    protected void Awake()
    {
        _agent = GetComponent<NavMeshAgent>();
        _animator = GetComponent<Animator>();

        turningDeadzone *= Mathf.Deg2Rad;
    }

    private void Update()
    {
        if (photonView.isMine)
        {
            SpeedUpdate();
            JumpCheckUpdate();
        }
    }

    private void SpeedUpdate()
    {
        if (_animator != null && _agent != null)
        {
            if (!_agent.pathPending)
            {
                if (_agent.remainingDistance <= _agent.stoppingDistance)
                {
                    if (!_agent.hasPath || _agent.velocity.sqrMagnitude == 0f)
                    {
                        speed = 0.0f;
                        _animator.SetFloat(AnimatorSpeed, speed);
                        return;
                    }
                }

                if (_agent.desiredVelocity != Vector3.zero)
                {
                    speed = Vector3.Project(_agent.desiredVelocity, Vector3.forward).magnitude * _agent.speed;
                }

                _animator.SetFloat(AnimatorSpeed, speed);

                // Find angle for rotation
                float angle = Vector3.Angle(transform.forward, _agent.desiredVelocity) * Mathf.Deg2Rad;

                // Use deadzone to determine if rotation is needed
                if (Mathf.Abs(angle) <= turningDeadzone)
                {
                    transform.LookAt(transform.position + _agent.desiredVelocity);
                }
                else
                {
                    transform.rotation = Quaternion.Lerp(
                        transform.rotation,
                        Quaternion.LookRotation(_agent.desiredVelocity),
                        Time.deltaTime * angularDampeningTime
                        );
                }
            }
        }
    }

    private void JumpCheckUpdate()
    {
        if (_agent != null && _animator != null)
        {
            if (_agent.isOnOffMeshLink)
            {
                if (!jumping)
                {
                    jumping = true;
                    photonView.RPC("RPC_TriggerJump", PhotonTargets.All);
                }
            }
            else
            {
                jumping = false;
            }
        }
    }

    public virtual void OnAnimatorMove()
    {
        _agent.velocity = _animator.deltaPosition / Time.deltaTime;
    }

    private void OnDrawGizmos()
    {
        if (_agent != null && _agent.hasPath)
        {
            Gizmos.color = debugDestLine;
            var path = _agent.path;
            for (int i = 1; i < path.corners.Length; i++)
            {
                Gizmos.DrawLine(path.corners[i - 1], path.corners[i]);
            }
        }
    }


    [PunRPC]
    protected void RPC_TriggerJump()
    {
        if (_animator != null)
        {
            _animator.SetTrigger(JumpTrigger);
        }
    }

    public void OnPhotonSerializeView(PhotonStream stream, PhotonMessageInfo info)
    {
        if (stream.isWriting)
        {
            stream.SendNext(speed);
        }
        else
        {
            speed = (float)stream.ReceiveNext();
        }
    }
}
