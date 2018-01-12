using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Hysteresis : MonoBehaviour
{
    [SerializeField]
    private GameObject _targetObject;
    public float kh;

    public delegate void OnHysteresisFinsih();

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        HysteresisUpdate();
    }

    private void HysteresisUpdate()
    {
        transform.position += kh * (_targetObject.transform.position - transform.position);
    }

    public void SetTarget(GameObject target)
    {
        _targetObject = target;
    }

}
