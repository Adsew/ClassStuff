using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Playables;
using UnityEngine.Animations;

public class PlayableSimple : MonoBehaviour {

    private PlayableGraph playGraph;
    private AnimationMixerPlayable moveMix;
    private AnimationMixerPlayable punchMix;
    private Animator animator;

    public AnimationClip idle;
    public AnimationClip walk;
    public AnimationClip punch;

    [Range(0.0f, 1.0f)]
    public float weight = 0.0f;

    [Range(0.0f, 1.0f)]
    public float punchWeight = 0.0f;

    // Use this for initialization
    void Start () {

        animator = GetComponent<Animator>();
        playGraph = PlayableGraph.Create();
        
        // Movement
        moveMix = AnimationMixerPlayable.Create(playGraph, 2);
        
        var clipPlayable1 = AnimationClipPlayable.Create(playGraph, idle);
        var clipPlayable2 = AnimationClipPlayable.Create(playGraph, walk);

        playGraph.Connect(clipPlayable1, 0, moveMix, 1);
        playGraph.Connect(clipPlayable2, 0, moveMix, 0);

        // Punching layer
        punchMix = AnimationMixerPlayable.Create(playGraph, 2);

        var clipPlayable3 = AnimationClipPlayable.Create(playGraph, punch);

        playGraph.Connect(moveMix, 0, punchMix, 1);
        playGraph.Connect(clipPlayable3, 0, punchMix, 0);

        var playableOut = AnimationPlayableOutput.Create(playGraph, "Animation", animator);
        playableOut.SetSourcePlayable(punchMix);

        playGraph.Play();

        GraphVisualizerClient.Show(playGraph, "AnimationWithPunch");
    }
	
	// Update is called once per frame
	void Update () {

        moveMix.SetInputWeight(0, weight);
        moveMix.SetInputWeight(1, 1.0f - weight);

        punchMix.SetInputWeight(0, punchWeight);
        punchMix.SetInputWeight(1, 1.0f - punchWeight);

        transform.position = Vector3.zero;
    }
}
