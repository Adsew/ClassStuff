using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

namespace UnityEditor
{
	[CreateAssetMenu]
	[CustomGridBrush(false, true, false, "Prefab Brush")]
	public class PrefabBrush : GridBrushBase
	{
		public GameObject mPrefab;
		public int mZ;

		public override void Paint(GridLayout grid, GameObject brushTarget, Vector3Int position)
		{
			// Do not allow editing palettes
			if (brushTarget.layer == 31)
				return;

			GameObject instance = (GameObject) PrefabUtility.InstantiatePrefab(mPrefab);
			Undo.RegisterCreatedObjectUndo((Object)instance, "Paint Prefabs");
			if (instance != null)
			{
				instance.transform.SetParent(brushTarget.transform);
				instance.transform.position = grid.LocalToWorld(grid.CellToLocalInterpolated(new Vector3Int(position.x, position.y, mZ) + new Vector3(.5f, .5f, .5f)));
			}
		}

		public override void Erase(GridLayout grid, GameObject brushTarget, Vector3Int position)
		{
			// Do not allow editing palettes
			if (brushTarget.layer == 31)
				return;

			Transform erased = GetObjectInCell(grid, brushTarget.transform, new Vector3Int(position.x, position.y, mZ));
			if (erased != null)
				Undo.DestroyObjectImmediate(erased.gameObject);
		}

		private static Transform GetObjectInCell(GridLayout grid, Transform parent, Vector3Int position)
		{
			int childCount = parent.childCount;
			Vector3 min = grid.LocalToWorld(grid.CellToLocalInterpolated(position));
			Vector3 max = grid.LocalToWorld(grid.CellToLocalInterpolated(position + Vector3Int.one));
			Bounds bounds = new Bounds((max + min)*.5f, max - min);

			for (int i = 0; i < childCount; i++)
			{
				Transform child = parent.GetChild(i);
				if (bounds.Contains(child.position))
					return child;
			}
			return null;
		}
	}

	[CustomEditor(typeof(PrefabBrush))]
	public class PrefabBrushEditor : GridBrushEditorBase
	{
		private PrefabBrush prefabBrush { get { return target as PrefabBrush; } }

		private SerializedProperty m_Prefabs;
		private SerializedObject m_SerializedObject;

		protected void OnEnable()
		{
			m_SerializedObject = new SerializedObject(target);
			m_Prefabs = m_SerializedObject.FindProperty("mPrefab");
		}

		public override void OnPaintInspectorGUI()
		{
			m_SerializedObject.UpdateIfRequiredOrScript();
				
			EditorGUILayout.PropertyField(m_Prefabs, true);
			m_SerializedObject.ApplyModifiedPropertiesWithoutUndo();
		}
	}
}
