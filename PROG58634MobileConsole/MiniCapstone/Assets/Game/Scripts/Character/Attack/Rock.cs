using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rock : Photon.PunBehaviour
{
    [HideInInspector]
    public AttackController attackController;
    public ParabolicData launchData;

    public Color gizmoColor = Color.grey;

    private void Start()
    {
        // ignore collisions
        if (attackController != null)
        {
            var collider = attackController.GetComponent<Collider>();
            if (collider != null)
            {
                var myCollider = GetComponent<Collider>();
                if (myCollider != null)
                {
                    Physics.IgnoreCollision(collider, myCollider);
                }
            }
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (PhotonNetwork.isMasterClient)
        {
            if (attackController != null)
            {
                var gameCharacter = collision.gameObject.GetComponent<GameCharacter>();
                if (gameCharacter != null)
                {
                    attackController.ApplyDamage(gameCharacter);
                }
            }
        }
        Destroy(gameObject);
    }

    private void OnDrawGizmos()
    {
        if (launchData.IsValid)
        {
            Gizmos.color = gizmoColor;
            float timeStep = 20.0f;
            Vector3 prevPos = transform.position;
            for (float i = 0.0f; i < timeStep; i++)
            {
                float simTime = i / timeStep * launchData.Duration;
                Vector3 simDisp = launchData.InitialVelocity * simTime + Physics.gravity * simTime * simTime / 2.0f;
                Vector3 nextPos = transform.position + simDisp;
                Gizmos.DrawLine(prevPos, nextPos);
                prevPos = nextPos;
            }
        }
    }
}
