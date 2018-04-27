using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;

public class LocalCameraController : Photon.PunBehaviour {
	private CinemachineVirtualCamera _cam = null;

	// Use this for initialization
	private void Start ()
    {
	    if (!photonView.isMine) return;
	    CinemachineBrain brain = Camera.main.GetComponent<CinemachineBrain>();

	    if (brain == null) return;
	    _cam = brain.ActiveVirtualCamera as CinemachineVirtualCamera;

	    if (_cam == null) return;
	    _cam.Follow = transform;
	    _cam.LookAt = transform;
    }
}
