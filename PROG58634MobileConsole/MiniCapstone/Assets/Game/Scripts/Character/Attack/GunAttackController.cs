using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BehaviorDesigner;
using BehaviorDesigner.Runtime;

public class GunAttackController : AttackController {

    public string bdTargetName;
    public Transform gunBarrel;
    public float firingRange = 20;

    private BehaviorTree tree = null;

    protected override void Start()
    {
        base.Start();
        tree = GetComponent<BehaviorTree>();
    }

    public override void StartAttack()
    {
        if (CanAttack)
        {
            if (_animator != null && !string.IsNullOrEmpty(AttackTrigger))
            {
                _animator.SetTrigger(AttackTrigger);
                StartCoroutine(Attacking());
            }
        }
    }

    public override void FinishAttack()
    {
        if (photonView.isMine)
        {
            FiringBullet();
        }
    }
    
    private void FiringBullet()
    {
        if (tree == null || gunBarrel == null)
        {
            throw new System.NullReferenceException("Cannotfire bullet without a valid tree or firing position");
        }
        
        var sharedVar = tree.GetVariable(bdTargetName);
        if (sharedVar != null)
        {
            var targetVar = sharedVar as SharedGameObject;
            if (targetVar != null && targetVar.Value != null)
            {
                RaycastHit hit;
                
                Debug.DrawRay(gunBarrel.position, targetVar.Value.transform.position - gunBarrel.position, Color.red);
                if (Physics.Raycast(gunBarrel.position, targetVar.Value.transform.position - gunBarrel.position, out hit, firingRange))
                {
                    GameCharacter charHit = hit.collider.gameObject.GetComponent<GameCharacter>();

                    if (charHit != null)
                    {
                        ApplyDamage(charHit);
                        Debug.DrawRay(gunBarrel.position, targetVar.Value.transform.position - gunBarrel.position, Color.green);
                    }
                }
            }
        }
    }
}
