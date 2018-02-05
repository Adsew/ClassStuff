using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ATransferGameObject : MonoBehaviour {

    public GameObject toTransfer;

    public void TransferGameObject(GameObject transferTo) {

        if (toTransfer != null && transferTo != null) {

            toTransfer.transform.parent = transferTo.transform;
            toTransfer.SetActive(true);
        }
    }
}
