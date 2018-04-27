using UnityEngine;

public class ApplyDamage : MonoBehaviour
{
    [Tooltip("AttackController is set if not set by start of component.")]
    public AttackController AttackController;
    private IsTriggerable _triggerable;

    private void Start()
    {
        _triggerable = GetComponent<IsTriggerable>();
        if (AttackController == null)
        {
            AttackController = GetComponentInParent<AttackController>();
        }
    }

    public void AttackCharacter()
    {
        Debug.Log("Attacking Character");
        if (_triggerable == null) return;
        GameObject lastTriggered = _triggerable.LastGameObject;
        if (lastTriggered == null) return;
        Debug.Log("Getting GameCharacter component from last game object");
        GameCharacter gameCharacter = lastTriggered.GetComponent<GameCharacter>();
        if (gameCharacter != null && AttackController != null)
        {
            Debug.Log("Applying damage");
            AttackController.ApplyDamage(gameCharacter);
        }
    }
}
