using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Experimental
{
    public class Billboard : MonoBehaviour
    {
        public enum MODE
        {
            Left,
            Forward
        }
        public MODE mode;

        private void FixedUpdate()
        {
            Vector3 camPos = Camera.main.transform.position;

            Vector3 dir = transform.position - camPos;

            if (mode == MODE.Left)
            {
                transform.right = -dir;
            }
            else if (mode == MODE.Forward)
            {
                transform.forward = dir;
            }
        }
    }
}