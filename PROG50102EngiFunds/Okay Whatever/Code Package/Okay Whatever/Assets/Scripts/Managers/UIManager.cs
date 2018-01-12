using System.Collections.Generic;
using UnityEngine;

public class UIManager : MonoBehaviour
{
    //---------------------------------------
    //  UIManager Singleton
    //
    private static UIManager _instance;
    public static UIManager Instance
    {
        get { return _instance; }
    }

    public List<IsUIPanel> panels;

    public static int LoadLevelPanelID = 5;

    private IsUIPanel _currentPanel = null;
    private IsUIPanel _prevPanel = null;

    // Use this for initialization

    private void Awake()
    {
        if (_instance == null)
        {
            _instance = this;
        }
        else
        {
            Destroy(this);
            return;
        }
    }
    void Start()
    {


        DeactivateAllPanels();
    }

    public IsUIPanel GetPanelById(int id)
    {
        if (id >= 0 || id < panels.Count)
        {
            return panels[id];
        }
        return null;
    }

    public void SetPanelID(int newID)
    {
        _prevPanel = _currentPanel;

        if (_prevPanel != null)
        {
            _prevPanel.gameObject.SetActive(false);
        }

        _currentPanel = null;   // used to not give false positives

        foreach (IsUIPanel isuip in panels)
        {
            if (isuip.ID == newID)
            {
                _currentPanel = isuip;
                _currentPanel.state = IsUIPanel.eUIPanelState.on;
                _currentPanel.gameObject.SetActive(true);
                return;
            }
        }
    }

    public void DeactivateAllPanels()
    {
        _prevPanel = _currentPanel;
        foreach (IsUIPanel isuip in panels)
        {
            isuip.state = IsUIPanel.eUIPanelState.off;
            isuip.gameObject.SetActive(false);
        }
        _currentPanel = null;
    }

    public void DeactivateCurrentPanel()
    {
        if (_currentPanel != null)
        {
            _currentPanel.state = IsUIPanel.eUIPanelState.off;
            _currentPanel.gameObject.SetActive(false);
        }
        _prevPanel = _currentPanel;
        _currentPanel = null;
    }

    public void ActivateCurrentPanel()
    {
        if (_currentPanel != null)
        {
            _currentPanel.gameObject.SetActive(true);
        }
    }

    public void SetPrevToCurrent()
    {
        _currentPanel = _prevPanel;
    }
}
