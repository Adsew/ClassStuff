using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FadeInFadeOut : MonoBehaviour
{
    [Range(0.1f, 10.0f)]
    public float FadeIn = 1.0f;
    [Range(0.1f, 10.0f)]
    public float Wait = 1.0f;
    [Range(0.1f, 10.0f)]
    public float FadeOut = 1.0f;
    public bool ChangeScale = false;
    public bool DestroyGO = false;

    private Renderer render;
    private Vector3 origScale = Vector3.zero;

    // Use this for initialization
    void Start()
    {
        render = GetComponent<Renderer>();
        if (ChangeScale)
        {
            origScale = transform.localScale;
            transform.localScale = Vector3.zero;
        }
        StartCoroutine(Fade());
    }

    IEnumerator Fade()
    {
        if (render != null)
        {
            float elapsed = 0.0f;
            Debug.Log("FadeIn: " + elapsed);
            while (elapsed <= FadeIn)
            {
                Debug.Log("Elapsed: " + elapsed);
                Color color = render.material.color;
                color.a = Mathf.Lerp(0.0f, 1.0f, elapsed / FadeIn);
                render.material.color = color;

                if (ChangeScale)
                {
                    transform.localScale = Vector3.Lerp(Vector3.zero, origScale, elapsed / FadeIn);
                }

                elapsed += Time.deltaTime;
                yield return null;
            }

            elapsed = 0.0f;

            yield return new WaitForSeconds(Wait);

            Debug.Log("Fade Out: " + elapsed);
            while (elapsed <= FadeOut)
            {
                Debug.Log("Elapsed: " + elapsed);
                Color color = render.material.color;
                color.a = Mathf.Lerp(1.0f, 0.0f, elapsed / FadeOut);
                render.material.color = color;

                if (ChangeScale)
                {
                    transform.localScale = Vector3.Lerp(origScale, Vector3.zero, elapsed / FadeIn);
                }

                elapsed += Time.deltaTime;
                yield return null;
            }

            if (DestroyGO)
            {
                Destroy(gameObject);
            }
        }
    }
}
