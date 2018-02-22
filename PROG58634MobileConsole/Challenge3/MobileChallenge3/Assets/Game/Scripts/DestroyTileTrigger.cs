using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class DestroyTileTrigger : MonoBehaviour {

    private Tilemap tilemap = null;

    private void Start() {

        if (tilemap == null) {

            tilemap = GetComponent<Tilemap>();
        }
    }

    private void OnTriggerEnter2D(Collider2D collision) {

        if (collision.gameObject.GetComponent<FireballTriggerDestroy>() != null) {
            
            Vector3Int pos = tilemap.WorldToCell(collision.transform.position);
            
            Vector3 unit = collision.transform.up;

            pos -= new Vector3Int((int)unit.x, (int)unit.y, 0); // Due to the collision occuring in adjusent cells
            
            tilemap.SetTile(pos, null);
        }
    }
}