using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;  // Need this for asset post processor

public class SpriteProcessor : AssetPostprocessor
{

    public string newName;

    public void OnPostprocessTexture(Texture2D texture) { // Triggers on new file coming in
        
        // check if asset processed in the folder
        string lowerCaseAssetPath = assetPath.ToLower(); // Get folder we are in
        bool isInSpriteDirectory = lowerCaseAssetPath.IndexOf("/sprite/") != -1;    // Lets us know if it ended up in the sprite folder

        if (isInSpriteDirectory) {

            TextureImporter textureImporter = (TextureImporter)assetImporter;
            textureImporter.textureType = TextureImporterType.Sprite;   // Change sprite's assets
            textureImporter.spriteImportMode = SpriteImportMode.Multiple;
            textureImporter.filterMode = FilterMode.Trilinear;
        }
    }

	// Use this for initialization
	void Start () {         // These are all callbacks these 2 are automatic but there are tons
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
