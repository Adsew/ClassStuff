using UnityEngine;
using UnityEngine.Events;

public class IsTriggerable : MonoBehaviour
{
    public GameObject Last;
    public GameObject LastGameObject { get; private set; }

    public UnityEvent events;

    private void OnTriggerEnter(Collider other)
    {
        Debug.Log("Triggered");
        LastGameObject = other.gameObject;
        Last = other.gameObject;
        if (events != null)
        {
            events.Invoke();
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        LastGameObject = collision.gameObject;

        if (events != null)
        {
            events.Invoke();
        }
    }
}
