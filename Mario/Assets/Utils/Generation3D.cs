using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;


public class Generation3D : MonoBehaviour {


    //script a mettre sur tilemap dans /Grid/TileMap
    //mettre le fichier "Cub" dans un dossier Resources dans assets


    Tilemap tilemap;

	BoundsInt bounds ;
	TileBase[] allTiles;

    public 

	// Use this for initialization
	void Start () {
        tilemap = GetComponent<Tilemap>();
        bounds = tilemap.cellBounds;
        allTiles = tilemap.GetTilesBlock(bounds);

        for (int x = 0; x < bounds.size.x; x++) {
			for (int y = 0; y < bounds.size.y; y++) {



                TileBase tile = allTiles[x + y * bounds.size.x];

                if (tile != null)
                {

                    Vector3Int v = new Vector3Int(x, y, 0);
                    /*
                    GridLayout gridLayout = transform.parent.GetComponentInParent<GridLayout>();//change rien
                    Vector3 v2 = gridLayout.CellToWorld(v);//change rien
                    */
                    Instantiate(Resources.Load("Underground"), v, Quaternion.identity);
                }
            }
		}        


	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
