using UnityEngine;
using UnityEngine.UI;

public class GameCharacter : Photon.PunBehaviour
{
    public int Health { get { return _health; } }
    private EventBehaviour _eventBehaviour;
    public Text HealthText;
    [SerializeField]
    private int _health = 100;
    [SerializeField]
    private int _maxHealth = 100;

    public string HUDName = "InGameHUD";

    private CharacterDied _characterDiedEvent;

    private void Awake()
    {
        _characterDiedEvent = new CharacterDied(this);
    }

    private void Start()
    {
        _eventBehaviour = GetComponent<EventBehaviour>();

        if (photonView.isMine && GetComponent<PlayerMovement>() != null)
        {
            UIMenu hud = UIManager.Instance.GetUIMenu(HUDName);

            if (hud != null)
            {
                HealthText = hud.GetComponentInChildren<Text>();

                if (HealthText != null)
                {
                    HealthText.text = "Health: " + _health;
                }
            }
        }
    }

    public void TakeDamage(int damage)
    {
        if (_health > 0)
        {
            Debug.Assert(damage < 0, "Damage on a character should be less than 0");
            
            photonView.RPC("RPC_UpdateHealth", PhotonTargets.All, damage);
        }
    }

    public void Heal(int amount)
    {
        if (amount > 0)
        {
            _health += amount;

            if (_health > _maxHealth)
            {
                _health = _maxHealth;
            }

            if (HealthText != null)
            {
                HealthText.text = "Health: " + _health;
            }

            photonView.RPC("RPC_UpdateHealth", photonView.owner, _health);
        }
    }

    [PunRPC]
    protected void RPC_UpdateHealth(int damage)
    {
        _health += damage;
        if (_health <= 0)
        {
            _health = 0;
            if (photonView.isMine)
            {
                if (_eventBehaviour != null)
                {
                    _eventBehaviour.Handler.Invoke(_characterDiedEvent);
                }
            }
        }

        if (photonView.isMine && HealthText != null)
        {
            HealthText.text = "Health: " + _health;
        }
    }

    //public void OnPhotonSerializeView(PhotonStream stream, PhotonMessageInfo info)
    //{
    //    if (stream.isWriting)
    //    {
    //        stream.SendNext(_health);
    //    }
    //    else
    //    {
    //        _health = (int)stream.ReceiveNext();
    //    }
    //}
}
