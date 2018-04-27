using UnityEngine;
using System.Collections.Generic;
using System.Collections;

public class AttackController : Photon.PunBehaviour
{
    public string AttackTrigger;
    public string AbilityTrigger;
    public string AttackState;

    public WeaponData WeaponData;
    protected BaseAbility _ability;
    protected Animator _animator;

    [SerializeField]
    protected List<BoxCollider> _attackColliders = new List<BoxCollider>();
    protected EventBehaviour _eventBehaviour;

    public bool CanAttack { get; protected set; }
    public bool CanUseAbility { get; protected set; }

    private void Awake()
    {
        CanAttack = true;
        CanUseAbility = true;
    }

    protected virtual void Start()
    {
        _animator = GetComponent<Animator>();
        _eventBehaviour = GetComponent<EventBehaviour>();
        _ability = GetComponentInChildren<BaseAbility>();

        DisableAttackVolume();
    }

    private void OnEnable()
    {
        if (_eventBehaviour == null)
        {
            _eventBehaviour = GetComponent<EventBehaviour>();
        }

        if (_eventBehaviour != null)
        {
            _eventBehaviour.Handler.AddListener<AttackEvent>(OnAttack);
            _eventBehaviour.Handler.AddListener<AbilityEvent>(OnAbility);
        }
    }

    private void OnDisable()
    {
        if (_eventBehaviour != null)
        {
            _eventBehaviour.Handler.RemoveListener<AttackEvent>(OnAttack);
            _eventBehaviour.Handler.RemoveListener<AbilityEvent>(OnAbility);
        }
    }

    public void OnAttack(AttackEvent e)
    {
        StartAttack();
    }

    public void OnAbility(AbilityEvent e)
    {
        TriggerAbility();
    }

    public void TriggerAbility()
    {
        if (CanUseAbility)
        {
            CanUseAbility = false;

            photonView.RPC("RPC_TriggerAbilityAnimation", PhotonTargets.All);

            if (photonView.isMine)
            {
                if (_ability != null)
                {
                    _ability.Execute();
                }
            }
        }
    }

    public void FinishAbility()
    {
        CanUseAbility = true;
        if (photonView.isMine)
        {
            if (_ability != null)
            {
                _ability.Finish();
            }
        }
    }

    protected IEnumerator Attacking()
    {
        CanAttack = false;

        while (!_animator.GetCurrentAnimatorStateInfo(0).IsName(AttackState)) { yield return null; }
        while (_animator.GetCurrentAnimatorStateInfo(0).IsName(AttackState)) { yield return null; }

        CanAttack = true;
        FinishAttack();
    }

    public virtual void StartAttack()
    {
        if (CanAttack)
        {
            CanAttack = false;

            if (_animator != null && !string.IsNullOrEmpty(AttackTrigger))
            {
                photonView.RPC("RPC_TriggerAttackAnimation", PhotonTargets.All);
                if (photonView.isMine)
                {
                    EnableAttackVolume();
                }
            }
        }
    }

    public virtual void FinishAttack()
    {
        CanAttack = true;
        if (photonView.isMine)
        {
            DisableAttackVolume();
        }
    }

    public void EnableAttackVolume()
    {
        if (_attackColliders != null)
        {
            foreach (BoxCollider attackCollider in _attackColliders)
            {
                attackCollider.gameObject.SetActive(true);
            }
        }
    }

    public void DisableAttackVolume()
    {
        if (_attackColliders != null)
        {
            foreach (BoxCollider attackCollider in _attackColliders)
            {
                attackCollider.gameObject.SetActive(false);
            }
        }
    }

    public void ApplyDamage(GameCharacter gameCharacter)
    {
        if (gameCharacter != null)
        {
            if (WeaponData != null)
            {
                gameCharacter.TakeDamage(WeaponData.damage);
            }
            else
            {
                Debug.LogError("Cannot Apply Damage with no Weapon Data");
            }
        }
    }

    [PunRPC]
    protected void RPC_TriggerAttackAnimation()
    {
        if (_animator != null)
        {
            _animator.SetTrigger(AttackTrigger);
        }
    }

    [PunRPC]
    protected void RPC_TriggerAbilityAnimation()
    {
        if (_animator != null)
        {
            _animator.SetTrigger(AbilityTrigger);
        }
    }
}
