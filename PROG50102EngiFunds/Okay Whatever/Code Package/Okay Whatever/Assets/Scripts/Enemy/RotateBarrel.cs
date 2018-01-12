using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotateBarrel : MonoBehaviour
{

    private Vector3 mPreviousPosition;

    private void Start()
    {
        mPreviousPosition = this.gameObject.transform.position;
        this.transform.root.SendMessage("registerListenerBarrelReachedEnd", this.gameObject);
    }

    // Update is called once per frame
    void Update()
    {
        rotateBarrel();
    }

    private void rotateBarrel()
    {
        Vector3 direction = (this.gameObject.transform.position - mPreviousPosition).normalized;
        float dx = direction.x;
        this.transform.Rotate(0, 0, -8 * dx, Space.World);

        mPreviousPosition = this.gameObject.transform.position;
    }

    public void OnSplineEnded()
    {
        Destroy(this);
    }
}
