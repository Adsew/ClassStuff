using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
//using AOT;

public class ObjectiveCallback : MonoBehaviour {

	#if UNITY_TVOS
	[DllImport ("__Internal")]
	private static extern int _add(int x, int y);
	#endif

	// Use this for initialization
	void Start () {

		#if UNITY_TVOS
		Debug.Log(_add(1, 1));
		#endif
	}
	
	// Update is called once per frame
	void Update () {

		#if UNITY_TVOS
		Debug.Log("Hello from update. WOrkn on TV");
		Debug.Log(_add(1,1));
		#endif
	}
}
