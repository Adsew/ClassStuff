using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyCommands : MonoBehaviour
{
    private Animator mAnimator;

    public GameObject barrelPrefab;
    public Transform initialBarrelPosition;
    public Transform leftHandPosition;

    private GameObject mCurrentBarrel;
    private float deltaX;

    private bool isAttachToHand = false;

    // Use this for initialization
    void Start()
    {
        mAnimator = GetComponent<Animator>();
        EnemyManager.Instance.setBossScript(this);
    }

    // Update is called once per frame
    void Update()
    {
        if (mCurrentBarrel != null)
        {
            if (isAttachToHand)
            {
                Vector3 lastPosition = mCurrentBarrel.transform.position;
                lastPosition.x = leftHandPosition.transform.position.x + deltaX;
                mCurrentBarrel.transform.position = lastPosition;
            }

            mCurrentBarrel.transform.rotation = initialBarrelPosition.transform.rotation;
        }
    }

    public void spawnBarrel()
    {
        if (mCurrentBarrel == null)
        {
            mAnimator.SetTrigger("throw");
            mCurrentBarrel = Instantiate(barrelPrefab);
            mCurrentBarrel.transform.position = initialBarrelPosition.transform.position;
            mCurrentBarrel.transform.rotation = initialBarrelPosition.transform.rotation;
        }
    }

    public void spawnFireEnemy()
    {
        if (mCurrentBarrel == null)
        {
            mAnimator.SetTrigger("throw");
            mCurrentBarrel = Instantiate(barrelPrefab);
            mCurrentBarrel.transform.position = initialBarrelPosition.transform.position;
            mCurrentBarrel.transform.rotation = initialBarrelPosition.transform.rotation;
        }
    }

    void throwAnimationEnd()
    {
        if (mCurrentBarrel != null)
        {
            EnemyManager.Instance.addBarrelToSpline(mCurrentBarrel);
        }
        mCurrentBarrel = null;
        isAttachToHand = false;
    }

    void attachToHand()
    {
        isAttachToHand = true;
        if (mCurrentBarrel != null)
        {
            deltaX = mCurrentBarrel.transform.position.x - leftHandPosition.transform.position.x;
        }
    }
}
