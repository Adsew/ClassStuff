using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PerlinNoiseTerrainGenerator : MonoBehaviour {

    private Terrain terrain;

    // This script is placed in public domain. The author takes no responsibility for any possible harm.
    public Texture2D heightMap;

    public bool gray = true;
    public int width = 128;
    public int height = 128;

    public float lacunarity = 6.18f;
    public float h = 0.69f;
    public float octaves = 8.379f;
    public float offset = 0.75f;
    public float scale = 0.09f;

    public float offsetPos = 0.0f;
    
    public void Start() {

        terrain = GetComponent<Terrain>();

        if (heightMap != null) {

            GenerateHeightmap();
        }
        else {

            calculatePerlin();
        }
    }
    
    public void GenerateHeightmap() {
        
        if (terrain != null) {

            int width = Mathf.Min(heightMap.width, 512);
            int height = Mathf.Min(heightMap.height, 512);

            // Build vertices and UVs
            Vector3[] vertices = new Vector3[height * width];

            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {

                    var pixelHeight = heightMap.GetPixel(x, y).grayscale;
                    Vector3 vertex = new Vector3(x, pixelHeight, y);
                    vertices[y * width + x] = vertex;
                }
            }

            float[,] verts = new float[height, width];

            foreach (Vector3 point in vertices) {

                verts[(int)point.z, (int)point.x] = point.y;
            }

            // Assign them to the terrain
            terrain.terrainData.SetHeights(0, 0, verts);
        }
    }

    public void calculatePerlin() {
        
        if (terrain != null) {

            Perlin perlin = new Perlin();
            FractalNoise fractal = new FractalNoise(h, lacunarity, octaves, perlin);

            float[,] verts = new float[height, width];

            for (var y = 0; y < height; y++) {
                for (var x = 0; x < width; x++) {

                    verts[y, x] = fractal.HybridMultifractal(x * scale + Time.deltaTime, y * scale + Time.deltaTime, offset) / 10.0f;
                }
            }

            terrain.terrainData.SetHeights(0, 0, verts);
        }
    }
}
