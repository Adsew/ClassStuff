using UnityEngine;

public class DestroyGO : MonoBehaviour
{
    public bool trigger = true;

    public void Destroy()
    {
        Debug.Log("Destroy GO called");
        if (trigger)
        {
            IsTriggerable triggerable = GetComponent<IsTriggerable>();
            if (triggerable != null)
            {
                GameObject lastTriggered = triggerable.LastGameObject;
                if (lastTriggered != null)
                {
                    Debug.Log("Destroy Last Triggered");
                    Destroy(lastTriggered);
                }
            }
        }
    }
}
