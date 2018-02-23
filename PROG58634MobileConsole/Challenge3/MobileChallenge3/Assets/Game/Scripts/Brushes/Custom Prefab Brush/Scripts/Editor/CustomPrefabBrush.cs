using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

namespace UnityEditor {

    [CreateAssetMenu]
    [CustomGridBrush(false, true, false, "Custom Prefab Brush")]
    public class CustomPrefabBrush : GridBrushBase {

        public GameObject prefabToPaint = null;

        public override void Paint(GridLayout grid, GameObject brushTarget, Vector3Int position) {
            
            if (prefabToPaint != null) {

                GameObject painted = Instantiate(prefabToPaint);

                if (painted != null) {

                    Undo.RegisterCreatedObjectUndo(painted, "Painted " + painted.name);

                    painted.transform.parent = brushTarget.transform;
                    painted.transform.position = position + new Vector3(0.5f, 0.5f, 0);
                }
            }
        }
    }
}
