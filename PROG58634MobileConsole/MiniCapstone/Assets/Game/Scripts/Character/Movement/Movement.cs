using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Movement : Photon.PunBehaviour, IPunObservable
{
    [SerializeField]
    public Track currentTrack;

    public float threshold = 0.1f;
    public float speed = 1.0f;
    public float jumpHeight;
    public Foot foot = null;
    public bool CanMove = true;

    protected float axisX = 0.0f;
    protected float axisY = 0.0f;
    protected bool jumpTrigger = false;

    private JumpZone upJumpZone;
    private JumpZone downJumpZone;
    private bool jumpInProgress = false;

    private Rigidbody rb;
    private Animator anim;

    /// <summary>
    /// Called on movement update before base movement update.
    /// </summary>
    protected virtual void MovementUpdate() { }

    /// <summary>
    /// Called on monobehaviour start after base start finishes.
    /// </summary>
    protected virtual void MovementStart() { }

    private void Start()
    {
        rb = GetComponent<Rigidbody>();
        anim = GetComponentInChildren<Animator>();

        MovementStart();
    }

    private void Update()
    {
        if (!CanMove) return;
        MovementUpdate();

        if (!jumpInProgress)
        {
            float z = axisX * -1.0f;

            if (currentTrack != null && rb != null)
            {
                if (z > threshold || z < -threshold)
                {
                    Vector3 newPos = new Vector3();
                    newPos.z += z * speed * Time.deltaTime;

                    transform.Translate(newPos, Space.World);

                    if (newPos.z != 0)
                    {
                        transform.right = newPos.normalized;
                    }
                }
            }

            if (jumpTrigger && foot != null && foot.Grounded())
            {
                if (axisY < 0.0f && downJumpZone != null)
                {
                    jumpInProgress = true;
                    StartCoroutine(Jump(downJumpZone));
                }
                else if (axisY > 0.0f && upJumpZone != null)
                {
                    jumpInProgress = true;
                    StartCoroutine(Jump(upJumpZone));
                }
                else
                {
                    JumpUp();
                }

                jumpTrigger = false;
            }
        }
    }

    private void FixedUpdate()
    {
        if (anim != null)
        {
            anim.SetFloat("AxisX", axisX);
            anim.SetFloat("AxisY", axisY);
        }
    }

    private void JumpUp()
    {
        rb.velocity = new Vector3(0.0f, jumpHeight, 0.0f);
    }

    IEnumerator Jump(JumpZone jumpZone)
    {
        JumpZone zone = jumpZone;
        float currentTime = Time.deltaTime;
        while (currentTime < 1.0f)
        {
            transform.position = zone.GetPosition(transform.position, currentTime, 1.0f);
            currentTime += Time.deltaTime;
            yield return null;
        }

        currentTrack = zone.endTrack;
        transform.position = new Vector3(currentTrack.start.position.x, currentTrack.start.position.y, transform.position.z);

        jumpInProgress = false;
    }

    public void SetJumpZone(JumpZone zone)
    {
        if (zone == null)
        {
            throw new System.ArgumentNullException("zone");
        }

        if (zone.method == JumpZone.ZoneMethod.Down)
        {
            downJumpZone = zone;
        }
        else if (zone.method == JumpZone.ZoneMethod.Up)
        {
            upJumpZone = zone;
        }
        else
        {
            Debug.LogWarning("Zone does not have method type set");
        }
    }

    public void RemoveJumpZone(JumpZone zone)
    {
        if (zone == null)
        {
            throw new System.ArgumentNullException("zone");
        }

        if (downJumpZone != null && zone.method == JumpZone.ZoneMethod.Down && downJumpZone.Equals(zone))
        {
            downJumpZone = null;
        }
        else if (upJumpZone != null && zone.method == JumpZone.ZoneMethod.Up && upJumpZone.Equals(zone))
        {
            upJumpZone = null;
        }
        else
        {
            Debug.LogWarning("Zone does not have method type set");
        }
    }

    [PunRPC]
    protected virtual void RPC_TriggerJump()
    {
        jumpTrigger = true;
    }

    public void OnPhotonSerializeView(PhotonStream stream, PhotonMessageInfo info)
    {
        if (stream.isWriting)
        {
            stream.SendNext(axisX);
            stream.SendNext(axisY);
            stream.SendNext(speed);

            if (currentTrack != null)
            {
                PhotonView view = currentTrack.GetComponent<PhotonView>();
                if (view != null)
                {
                    stream.SendNext(view.viewID);
                }
            }
        }
        else
        {
            axisX = (float)stream.ReceiveNext();
            axisY = (float)stream.ReceiveNext();
            speed = (float)stream.ReceiveNext();
            int viewID = (int)stream.ReceiveNext();
            PhotonView view = PhotonView.Find(viewID);
            if (view != null)
            {
                currentTrack = view.GetComponent<Track>();
            }
        }
    }
}
