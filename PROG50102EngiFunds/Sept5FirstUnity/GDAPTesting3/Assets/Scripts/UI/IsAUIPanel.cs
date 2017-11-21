using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsAUIPanel : MonoBehaviour {

    private Hysteresis h;

    public enum eUIPanelState {

        invalid = -1,
        off = 0,        // Default off in case need to initialize
        on = 1
    }

    public int id;
    public eUIPanelState state;

    public void SetState(eUIPanelState s) {

        state = s;
    }

	// Use this for initialization
	void Start () {

        h = this.gameObject.GetComponent<Hysteresis>();
	}
	
    public void IsAUIPanelUpdate() {

        // process my state according to state var
        switch (state) {

            case (eUIPanelState.invalid): {

                    break;
                }

            case (eUIPanelState.on): {

                    break;
                }
                
            case (eUIPanelState.off): {

                    break;
                }
        }
    }

	// Update is called once per frame
	void Update () {

        IsAUIPanelUpdate();
	}
}
