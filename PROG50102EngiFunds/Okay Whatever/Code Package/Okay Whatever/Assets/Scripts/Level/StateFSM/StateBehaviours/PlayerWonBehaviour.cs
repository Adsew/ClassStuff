using UnityEngine;

public class PlayerWonBehaviour : StateMachineBehaviour
{
    public int wonPanelID;
    // OnStateEnter is called when a transition starts and the state machine starts to evaluate this state
    override public void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        if (PlayerManager.Instance.activePlayer != null)
        {
            IsPlayer player = PlayerManager.Instance.activePlayer.GetComponent<IsPlayer>();
            if (player != null)
            {
                player.SetVictory();
            }

        }
        EnemyManager.Instance.PlayerWon();
        UIManager.Instance.SetPanelID(wonPanelID);
    }

    // OnStateUpdate is called on each Update frame between OnStateEnter and OnStateExit callbacks
    override public void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {

    }

    // OnStateExit is called when a transition ends and the state machine finishes evaluating this state
    override public void OnStateExit(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
    }
}
