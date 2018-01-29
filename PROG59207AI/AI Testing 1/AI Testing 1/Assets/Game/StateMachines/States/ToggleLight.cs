using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ToggleLight : StateMachineBehaviour {

    public string triggerName;

    public Light _light;

    public float delay;

    private float currentTime;

    // OnStateEnter is called when a transition starts and the state machine starts to evaluate this state
    override public void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {

        currentTime = delay;

        _light = animator.GetComponent<Light>();
    }

    // OnStateUpdate is called on each Update frame between OnStateEnter and OnStateExit callbacks
    override public void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {

        currentTime -= Time.deltaTime;

        if (currentTime < 0.0f) {

            _light.enabled = !_light.enabled;

            animator.SetTrigger(triggerName);
        }
    }

    // OnStateExit is called when a transition ends and the state machine finishes evaluating this state
    override public void OnStateExit(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {

    }
}
