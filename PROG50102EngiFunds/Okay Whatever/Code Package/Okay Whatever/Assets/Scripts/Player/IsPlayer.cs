using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsPlayer : MonoBehaviour
{
    public static IsPlayer This;

    private PlayerMovement myMovement = null;
    private PlayerAnimation myAnimation = null;

    public int lives = 3;

    public bool isDead;

    private AudioController deathAudioController;

    // Use this for initialization
    void Start()
    {
        if (This == null)
        {

            This = this;
        }

        if (myMovement == null)
        {

            myMovement = this.gameObject.GetComponent<PlayerMovement>();
        }

        if (myAnimation == null)
        {

            myAnimation = this.gameObject.GetComponent<PlayerAnimation>();
        }

        deathAudioController = GetComponent<AudioController>();
    }

    // Update is called once per frame
    void Update()
    {

    }

    public bool SetVictory()
    {

        if (!isDead)
        {

            if (myMovement != null)
            {

                myMovement.setMovementLock(true);
            }

            if (myAnimation != null)
            {

                myAnimation.setDancing();
            }

            return true;
        }

        return false;
    }

    public bool Die()
    {

        if (!isDead)
        {

            isDead = true;

            if (myMovement != null)
            {

                myMovement.setMovementLock(true);
            }

            if (myAnimation != null)
            {
                myAnimation.setPickup(); // Drops weapon if held
                myAnimation.setDying();
            }

            if (deathAudioController != null)
            {
                deathAudioController.PlayClip();
            }

            lives--;
            PlayerManager.Instance.PlayerDied();

            return true;
        }

        return false;
    }

    public bool Revive()
    {

        if (isDead)
        {

            isDead = false;

            if (myMovement != null)
            {

                myMovement.setMovementLock(false);
            }

            if (myAnimation != null)
            {

                myAnimation.setReviveFromDeath();
            }



            return true;
        }

        return false;
    }
}
