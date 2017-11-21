using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// Class shows and hides panels

public class UIMgr : MonoBehaviour {

    public static UIMgr Instance;
    public List<IsAUIPanel> panels;
    public GameObject onLoc;
    public GameObject offLoc;


    public int panelID;
    
    private int prevTickPanelID;

	// Use this for initialization
	void Start () {
		
        if (Instance == null) {

            Instance = this;
        }

        panelID = 1;
        prevTickPanelID = -1;

        foreach(IsAUIPanel iauip in panels) {

            Hysteresis h = iauip.gameObject.GetComponent<Hysteresis>();

            if (h != null) {

                h.setTgt(offLoc);
                h.kh = 0.1f;
            }
        }
	}
	
    public void SetPanelID(int id) {

        panelID = id;
    }

    public void UIMgrUpdate() {

        // Process current poanel id
        foreach (IsAUIPanel iap in panels) {

            if (iap.id == panelID) {

                iap.SetState(IsAUIPanel.eUIPanelState.on);

                Hysteresis h = iap.gameObject.GetComponent<Hysteresis>();

                if (h != null) {

                    h.setTgt(onLoc);
                    h.kh = 0.1f;
                }
            }
            else {

                iap.SetState(IsAUIPanel.eUIPanelState.off);

                Hysteresis h = iap.gameObject.GetComponent<Hysteresis>();

                if (h != null) {

                    h.setTgt(offLoc);
                    h.kh = 0.1f;
                }
            }
        }
        
        prevTickPanelID = panelID;
    }

	// Update is called once per frame
	void Update () {

        UIMgrUpdate();
	}
}
