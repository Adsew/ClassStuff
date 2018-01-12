using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectPositionTracker : MonoBehaviour {
    
    public GameObject trackObject = null;

    public enum Mode {

        LocalPosition,
        TruePosition,
        TrueYLocalXZ
    };

    public Mode mode = Mode.LocalPosition;

	// Use this for initialization
	void Start () {
		
	}
	
    private void TrackObjectUpdate() {

        if (trackObject != null) {

            if (mode == Mode.LocalPosition) {

                Vector3 pos = trackObject.transform.localPosition;

                pos.x = 0;
                pos.z = 0;

                this.gameObject.transform.localPosition = pos;
            }
            else if (mode == Mode.TruePosition) {
                
                this.gameObject.transform.position = trackObject.transform.position;
            }
            else if (mode == Mode.TrueYLocalXZ) {

                Transform trackTrans = trackObject.transform;
                Vector3 truePos = trackTrans.position;
                Vector3 localPos = trackTrans.localPosition;

                localPos.x = 0;
                localPos.z = 0;

                this.gameObject.transform.localPosition = localPos;

                Vector3 myTempPos = this.gameObject.transform.position;

                myTempPos.y = truePos.y;

                this.gameObject.transform.position = myTempPos;
            }
        }
    }

	// Update is called once per frame
	void Update () {

        TrackObjectUpdate();
	}
}
