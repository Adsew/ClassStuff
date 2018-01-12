using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsVictoryPosition : MonoBehaviour
{

    Animator princessAnim = null;
    AudioController audioController;

    public CameraFollow _cameraFollow;

    // Use this for initialization
    void Start()
    {

        audioController = GetComponentInParent<AudioController>();
        if (princessAnim == null)
        {

            princessAnim = this.gameObject.transform.parent.GetComponentInChildren<Animator>();
        }
    }

    private void OnTriggerEnter(Collider other)
    {

        IsPlayer player = other.gameObject.GetComponent<IsPlayer>();

        if (player != null)
        {
            player.SetVictory();
            player.transform.position = this.gameObject.transform.position;
            player.transform.eulerAngles = new Vector3(0, 180.0f, 0);
            Rigidbody pRB = player.gameObject.GetComponent<Rigidbody>();

            if (pRB != null)
            {

                pRB.velocity = new Vector3(0, 0, 0);
            }

            if (princessAnim != null)
            {

                princessAnim.SetTrigger("Victory");
            }

            if (audioController != null)
            {
                audioController.PlayClip();
            }

            _cameraFollow.MoveToVictory();

            GameStateManager.Instance.SetTrigger(GameStateManager.playerWon);
        }
    }

    // Update is called once per frame
    void Update()
    {

    }
}
