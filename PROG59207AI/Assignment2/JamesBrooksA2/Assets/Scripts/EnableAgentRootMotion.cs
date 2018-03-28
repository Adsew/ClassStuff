using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class EnableAgentRootMotion : MonoBehaviour {

    private NavMeshAgent agent = null;
    private Animator anim = null;

    // Use this for initialization
    void Start () {

        agent = GetComponent<NavMeshAgent>();
        anim = GetComponent<Animator>();
    }

    private void OnAnimatorMove() {

        agent.velocity = anim.deltaPosition / Time.deltaTime;
    }
}
