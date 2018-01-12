using UnityEngine;

public class PlayerViewer : MonoBehaviour
{
    [Range(0.0f, 180.0f)]
    public float rotationAmount = 0.01f;

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.LeftArrow))
        {
            transform.Rotate(new Vector3(0, 1, 0), -rotationAmount);
        }
        else if (Input.GetKeyDown(KeyCode.RightArrow))
        {
            transform.Rotate(new Vector3(0, 1, 0), rotationAmount);
        }
    }
}
