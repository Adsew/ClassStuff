using UnityEngine;

public class PlayerMovement : Movement, IInterestingObject
{
    [Header("Input")]
    public string horzName;
    public string vertName;
    public string jumpName;
    public string pauseName;

    public void OnInsideView(ViewObject view)
    {

    }

    protected override void MovementStart()
    {
#if UNITY_TVOS
        UnityEngine.Apple.TV.Remote.allowExitToHome = false;
        UnityEngine.Apple.TV.Remote.allowRemoteRotation = true;
#endif
    }
    protected override void MovementUpdate()
    {
        if (photonView.isMine)
        {
            axisX = Input.GetAxis(horzName);
            axisY = Input.GetAxis(vertName);

            if (Input.GetButtonDown(jumpName))
            {
                photonView.RPC("RPC_TriggerJump", PhotonTargets.All);
            }

            if (Input.GetButtonDown(pauseName))
            {
                UIManager.Instance.ShowMenu("Pause Menu");
            }
        }
    }
}
