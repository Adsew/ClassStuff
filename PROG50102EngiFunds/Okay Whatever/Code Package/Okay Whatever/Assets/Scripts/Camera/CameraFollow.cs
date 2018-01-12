using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraFollow : MonoBehaviour
{

    public IsCameraStartPoint camStartPoint;
    public IsCameraRig camRig;
    public IsCameraRig camVictory;

    [SerializeField]
    private GameObject _targetObject;
    public float kh;

    delegate void OnHysteresisFinish();
    OnHysteresisFinish _hysteresisFinished = null;

    [SerializeField]
    private float _finishedCamFollow = 0.05f;

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        HysteresisUpdate();
    }

    public void MoveToCameraRig()
    {
        SetTarget(camRig.gameObject);
    }

    public void MoveToStartPoint()
    {
        SetTarget(camStartPoint.gameObject);
    }

    public void MoveToVictory()
    {
        SetTarget(camVictory.gameObject);
    }

    // set the camera to the rig
    public void SetCameraToRig()
    {
        if (camRig != null)
        {
            SetCamera(camRig.gameObject);
        }
        _targetObject = null;
    }

    // set the camera to the start
    public void SetCameraToStart()
    {
        if (camStartPoint != null)
        {
            SetCamera(camStartPoint.gameObject);
        }
        _targetObject = null;
    }

    private void HysteresisUpdate()
    {
        if (_targetObject != null)
        {
            Vector3 dir = _targetObject.gameObject.transform.position - gameObject.transform.position;
            gameObject.transform.forward = Vector3.Slerp(gameObject.transform.forward, _targetObject.gameObject.transform.forward, Time.deltaTime);
            // check if camera has reached a distance considered to be finished
            if (Vector3.Distance(transform.position, _targetObject.transform.position) > _finishedCamFollow)
            {
                transform.position += kh * (dir);
            }
            else
            {
                SetCamera(_targetObject);
                // callback if set
                if (_hysteresisFinished != null)
                {
                    _hysteresisFinished();
                }
            }
        }
    }

    public void SetTarget(GameObject target)
    {
        _targetObject = target;
    }

    private void SetCamera(GameObject gObject)
    {
        transform.position = gObject.transform.position;
        transform.forward = gObject.transform.forward;
        transform.parent = gObject.transform;
    }
}
