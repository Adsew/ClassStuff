using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(AudioSource))]
public class IsPickupable : MonoBehaviour
{

    public GameObject pickupTrigger;
    private IsPickupTrigger trigger;

    private PlayerAnimation playerHeldBy = null;

    public AnimatorOverrideController animOverride;

    public List<GameObject> rightHandPoints;
    public List<GameObject> leftHandPoints;

    private bool timing = false;
    private float timer = 0.0f;
    public float duration = 10.0f;

    public AudioData audioData;
    public AudioSource audioSource;


    // Use this for initialization
    void Start()
    {
        audioSource = GetComponent<AudioSource>();

        if (trigger == null && pickupTrigger != null)
        {

            trigger = pickupTrigger.GetComponent<IsPickupTrigger>();
        }

        if (rightHandPoints.Count == 0)
        {

            IsRHGrabPosition[] rhs = this.gameObject.GetComponentsInChildren<IsRHGrabPosition>();

            foreach (IsRHGrabPosition rh in rhs)
            {

                rightHandPoints.Add(rh.gameObject);
            }
        }
    }

    private void TimeToDropUpdate()
    {

        if (timing)
        {

            timer += Time.deltaTime;

            if (timer >= duration)
            {

                playerHeldBy.setPickup();

                timing = false;
            }
        }
    }

    // Update is called once per frame
    void Update()
    {

        TimeToDropUpdate();
    }

    public void pickup(PlayerAnimation p)
    {

        playerHeldBy = p;

        trigger.setPickedUp();
        timing = true;
        timer = 0;

        if (audioData != null)
        {
            // play audio
            audioData.Play(audioSource);
        }
    }

    public void drop()
    {
        timing = false;
        timer = 0;
        playerHeldBy = null;

        this.gameObject.transform.parent = null;

        if (this.gameObject.GetComponent<Rigidbody>() == null)
        {

            this.gameObject.AddComponent<Rigidbody>();
        }

        if (audioData != null)
        {
            // stop playing
            audioData.Stop(audioSource);
        }
        //trigger.setDropped(); // Uncomment to allow pickingup after drop
    }

    public GameObject getClosestHandle(Vector3 pos)
    {

        GameObject closestGO = null;
        float shortestDist = 0;
        float distance = 0;

        foreach (GameObject handle in rightHandPoints)
        {

            if (closestGO == null)
            {

                closestGO = handle;

                shortestDist = Mathf.Abs(Vector3.Magnitude(handle.transform.position - pos));
            }
            else
            {

                distance = Mathf.Abs(Vector3.Magnitude(handle.transform.position - pos));

                if (distance < shortestDist)
                {

                    shortestDist = distance;
                    closestGO = handle;
                }
            }
        }

        return closestGO;
    }
}
