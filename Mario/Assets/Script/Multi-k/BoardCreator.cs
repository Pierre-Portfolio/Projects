using System.Collections;
using UnityEngine;
using UnityEngine.Tilemaps;

public class BoardCreator : MonoBehaviour
{
    // The type of tile that will be laid in a specific position.
    public enum TileType
    {
        Wall, Floor,
    }


    public Tilemap TiledMapSol;
    public Tilemap TiledMapMur;


    public int columns = 100;                                 // The number of columns on the board (how wide it will be).
    public int rows = 100;                                    // The number of rows on the board (how tall it will be).
    public IntRange numRooms = new IntRange(15, 20);         // The range of the number of rooms there can be.
    public IntRange roomWidth = new IntRange(3, 10);         // The range of widths rooms can have.
    public IntRange roomHeight = new IntRange(3, 10);        // The range of heights rooms can have.
    public IntRange corridorLength = new IntRange(6, 10);    // The range of lengths corridors between rooms can have.
    public TileBase[] floorTiles;                           // An array of floor tile prefabs.
    public TileBase[] wallTiles;                            // An array of wall tile prefabs.
    public TileBase[] outerWallTiles;                       // An array of outer wall tile prefabs.
    public GameObject player;

    private TileType[][] tiles;                               // A jagged array of tile types representing the board, like a grid.
    private Piece[] rooms;                                     // All the rooms that are created for this board.
    private Corridor[] corridors;                             // All the corridors that connect the rooms.
    public GameObject boardHolder;                           // GameObject that acts as a container for all other tiles.


    public TileBase coinHautDroite;
    public TileBase coinHautGauche;
    public TileBase coinBasDroite;
    public TileBase coinBasGauche;

    public TileBase haut;
    public TileBase droite;
    public TileBase gauche;
    public TileBase bas;

    public TileBase bordGaucheMur;
    public TileBase bordDroitMur;

    public TileBase murBon;

    public bool devTesting = false;

    private int valSeed;


    //A ABSOLUMENT OPTIMISER
    // POUR OPTIMISER ON PEUT PAR EXEMPLE COMPTER SI NB TRUE > 1

    byte ConvertToByte(BitArray bits)
    {
        byte[] bytes = new byte[1];
        bits.CopyTo(bytes, 0);
        return bytes[0];
    }





    public bool compareEqual(BitArray a, byte b)
    {

        return (ConvertToByte(a) == b);

    }

    public void reajusterTiles2()
    {

        //Vector3Int[] aDetruire = new Vector3Int[40];

        ArrayList aDetruire = new ArrayList();

        //ON PEUT UTILISER UN BITARRAY, PLUS LEGER EN MEMOIRE MAIS PLUS CHIANT A PARCOURIR

        //ON PEUT SURTOUT COMPARER AVEC DES BITS GENRE SI = 0xAB
        BitArray adjacents = new BitArray(8);


        int i;
        int j;
        for (i = 0; i <= columns; i++)
        {

            adjacents = new BitArray(8); ;

            for (j = 0; j <= rows; j++)
            {

                if (TiledMapMur.HasTile(new Vector3Int(i, j, 1)))
                {



                    adjacents.Set(0, TiledMapMur.HasTile(new Vector3Int(i - 1, j - 1, 1)));
                    adjacents.Set(1, TiledMapMur.HasTile(new Vector3Int(i, j - 1, 1)));
                    adjacents.Set(2, TiledMapMur.HasTile(new Vector3Int(i + 1, j - 1, 1)));

                    adjacents.Set(3, TiledMapMur.HasTile(new Vector3Int(i - 1, j, 1)));
                    adjacents.Set(4, TiledMapMur.HasTile(new Vector3Int(i + 1, j, 1)));

                    adjacents.Set(5, TiledMapMur.HasTile(new Vector3Int(i - 1, j + 1, 1)));
                    adjacents.Set(6, TiledMapMur.HasTile(new Vector3Int(i, j + 1, 1)));
                    adjacents.Set(7, TiledMapMur.HasTile(new Vector3Int(i + 1, j + 1, 1)));



                    //---------------------MURS ----------- //
                    if (compareEqual(adjacents, 0xD6) || compareEqual(adjacents, 0xF6) || compareEqual(adjacents, 0xD7))
                        TiledMapMur.SetTile(new Vector3Int(i, j, 1), droite);

                    if (compareEqual(adjacents, 0x6B) || compareEqual(adjacents, 0xEB) || compareEqual(adjacents, 0x6F))
                        TiledMapMur.SetTile(new Vector3Int(i, j, 1), gauche);

                    if (compareEqual(adjacents, 0x3F) || compareEqual(adjacents, 0x1F) || compareEqual(adjacents, 0x9F))
                    {
                        TiledMapMur.SetTile(new Vector3Int(i, j, 1), bas);
                        TiledMapMur.SetTile(new Vector3Int(i, j-1, 1), murBon);
                    }

                        if (compareEqual(adjacents, 0xF8) || compareEqual(adjacents, 0xFC) || compareEqual(adjacents, 0xF9))
                    { 
                        TiledMapMur.SetTile(new Vector3Int(i, j + 1, 1), haut);
                        TiledMapSol.SetTile(new Vector3Int(i, j+1, 1), null);
                        TiledMapMur.SetTile(new Vector3Int(i, j, 1), murBon);
                    }


                    //---------COINS-------//

                    if (compareEqual(adjacents, 0x7F))
                    {
                        TiledMapMur.SetTile(new Vector3Int(i, j, 1), coinBasGauche);
                        TiledMapMur.SetTile(new Vector3Int(i, j - 1, 1), murBon);
                    }
                    if (compareEqual(adjacents, 0xDF))
                    {
                        TiledMapMur.SetTile(new Vector3Int(i, j, 1), coinBasDroite);
                        TiledMapMur.SetTile(new Vector3Int(i, j - 1, 1), murBon);
                    }
                    if (compareEqual(adjacents, 0xFB))
                    {
                        TiledMapSol.SetTile(new Vector3Int(i, j+1, 1), null);
                        TiledMapMur.SetTile(new Vector3Int(i, j, 1), coinHautGauche);
                        TiledMapMur.SetTile(new Vector3Int(i, j + 1, 1), haut);
                    }

                    if (compareEqual(adjacents, 0xFE))
                    {
                        TiledMapSol.SetTile(new Vector3Int(i, j + 1, 1), null);
                        TiledMapMur.SetTile(new Vector3Int(i, j, 1), coinHautDroite);
                        TiledMapMur.SetTile(new Vector3Int(i, j + 1, 1), haut);
                    }


                    //BordMurs
                    if (compareEqual(adjacents, 0xD0))
                        TiledMapMur.SetTile(new Vector3Int(i, j, 1), bordGaucheMur);
                    if (compareEqual(adjacents, 0x68))
                        TiledMapMur.SetTile(new Vector3Int(i, j, 1), bordDroitMur);


                    //Mauvais Murs
                    if ( compareEqual(adjacents, 0x16) || compareEqual(adjacents, 0x0B))
                    {
                        aDetruire.Add(new Vector3Int(i, j, 1));

                    }
                    
                    if (compareEqual(adjacents, 0xD4) || compareEqual(adjacents, 0xF0) || compareEqual(adjacents, 0xE8) || compareEqual(adjacents, 0x69))
                    {
                        aDetruire.Add(new Vector3Int(i, j, 1));

                    }
                    if (compareEqual(adjacents, 0x96) || compareEqual(adjacents, 0x17) || compareEqual(adjacents, 0x0F) || compareEqual(adjacents, 0x2B))
                    {
                        aDetruire.Add(new Vector3Int(i, j, 1));

                    }

                }







            }
        }


        foreach (Vector3Int v in aDetruire)
        {
            TiledMapMur.SetTile(v, null);
        }
        supprimerMauvaisMurs();

    }

    public void supprimerMauvaisMurs() {

        int i, j;
        bool c1;
        bool c2;

        for (i = 0; i <= columns; i++) {


            for (j = 0; j <= rows; j++)
            {

                if (TiledMapMur.GetTile(new Vector3Int(i, j, 1)) == wallTiles[0])
                {

                    
                        TiledMapMur.SetTile(new Vector3Int(i, j, 1), null);
                        TiledMapSol.SetTile(new Vector3Int(i, j, 1), null);




                }





            }
        }

        for (i = 0; i <= columns; i++)
        {


            for (j = 0; j <= rows; j++)
            {
                c1 = (TiledMapSol.HasTile(new Vector3Int(i - 1, j, 1)) && (TiledMapSol.HasTile(new Vector3Int(i + 1, j, 1))));
                c2 = (TiledMapSol.HasTile(new Vector3Int(i, j - 1, 1)) && (TiledMapSol.HasTile(new Vector3Int(i, j + 1, 1))));
                if ((c1 || c2)) {

                    //TiledMapMur.SetTile(new Vector3Int(i, j, 1), null);
                    TiledMapSol.SetTile(new Vector3Int(i, j, 1), floorTiles[0]);
                }



            }
        }

    }

    private void OnPhotonEvent(byte eventCode, object content, int senderId) {


            RaiseEventOptions raiseEventOptions = new RaiseEventOptions { Receivers = ReceiverGroup.All };

            print("PhotonEvent");
            if (eventCode == 1 && PhotonNetwork.isMasterClient)
            {
                PhotonNetwork.RaiseEvent(0, valSeed, true, raiseEventOptions);
            }


            if (eventCode == 0 && valSeed == 0)
            {
                valSeed = (int)content;

                Random.InitState(valSeed);

                SetupTilesArray();

                CreateRoomsAndCorridors();

                SetTilesValuesForRooms();
                SetTilesValuesForCorridors();

                InstantiateTiles();
                InstantiateOuterWalls();

                reajusterTiles2();

                print("PhotonEvent" + valSeed);

            }


        

    }


    private void Start()
    {


    if (!devTesting)
    {

        RaiseEventOptions raiseEventOptions = new RaiseEventOptions { Receivers = ReceiverGroup.All };
        valSeed = 0;

        PhotonNetwork.OnEventCall += OnPhotonEvent;


        PhotonNetwork.RaiseEvent(1, 0, true, raiseEventOptions);
        //PhotonNetwork.RaiseEvent(0, valSeed, false, raiseEventOptions);



        if (PhotonNetwork.isMasterClient)
        {

            print("masterClient");

            valSeed = (int)Random.Range(1, 255);

            Random.InitState(valSeed);
            print("you are the hoost" + valSeed);
            // Create the board holder.
            //boardHolder = new GameObject("BoardHolder");


            SetupTilesArray();

            CreateRoomsAndCorridors();

            SetTilesValuesForRooms();
            SetTilesValuesForCorridors();

            InstantiateTiles();
            InstantiateOuterWalls();

            reajusterTiles2();

            print("masterClient" + valSeed);

        }
    }
    else {

        valSeed = (int)Random.Range(1, 255);

        Random.InitState(valSeed);
        // Create the board holder.
        //boardHolder = new GameObject("BoardHolder");


        SetupTilesArray();

        CreateRoomsAndCorridors();

        SetTilesValuesForRooms();
        SetTilesValuesForCorridors();

        InstantiateTiles();
        InstantiateOuterWalls();

        reajusterTiles2();

        print("Nombre de salles" + rooms.Length);

    }

    }


    void SetupTilesArray()
    {
        // Set the tiles jagged array to the correct width.
        tiles = new TileType[columns][];

        // Go through all the tile arrays...
        for (int i = 0; i < tiles.Length; i++)
        {
            // ... and set each tile array is the correct height.
            tiles[i] = new TileType[rows];
        }
    }


    void CreateRoomsAndCorridors()
    {
        // Create the rooms array with a random size.
        rooms = new Piece[numRooms.Random];

        // There should be one less corridor than there is rooms.
        corridors = new Corridor[rooms.Length - 1];

        // Create the first room and corridor.
        rooms[0] = new Piece();
        corridors[0] = new Corridor();

        // Setup the first room, there is no previous corridor so we do not use one.
        rooms[0].SetupRoom(roomWidth, roomHeight, columns, rows);

        // Setup the first corridor using the first room.
        corridors[0].SetupCorridor(rooms[0], corridorLength, roomWidth, roomHeight, columns, rows, true);

        for (int i = 1; i < rooms.Length; i++)
        {
            // Create a room.
            rooms[i] = new Piece();

            // Setup the room based on the previous corridor.
            rooms[i].SetupRoom(roomWidth, roomHeight, columns, rows, corridors[i - 1]);

            // If we haven't reached the end of the corridors array...
            if (i < corridors.Length)
            {
                // ... create a corridor.
                corridors[i] = new Corridor();

                // Setup the corridor based on the room that was just created.
                corridors[i].SetupCorridor(rooms[i], corridorLength, roomWidth, roomHeight, columns, rows, false);
            }

            if (i == rooms.Length * .5f)
            {
                Vector3 playerPos = new Vector3(rooms[i].xPos, rooms[i].yPos, 0);

                player.transform.position = playerPos;

                //Instantiate(player, playerPos, Quaternion.identity);
            }
        }

    }


    void SetTilesValuesForRooms()
    {
        // Go through all the rooms...
        for (int i = 0; i < rooms.Length; i++)
        {
            Piece currentRoom = rooms[i];

            // ... and for each room go through it's width.
            for (int j = 0; j < currentRoom.roomWidth; j++)
            {
                int xCoord = currentRoom.xPos + j;

                // For each horizontal tile, go up vertically through the room's height.
                for (int k = 0; k < currentRoom.roomHeight; k++)
                {
                    int yCoord = currentRoom.yPos + k;

                    // The coordinates in the jagged array are based on the room's position and it's width and height.
                    tiles[xCoord][yCoord] = TileType.Floor;
                }
            }
        }
    }


    void SetTilesValuesForCorridors()
    {
        // Go through every corridor...
        for (int i = 0; i < corridors.Length; i++)
        {
            Corridor currentCorridor = corridors[i];

            // and go through it's length.
            for (int j = 0; j < currentCorridor.corridorLength; j++)
            {
                // Start the coordinates at the start of the corridor.
                int xCoord = currentCorridor.startXPos;
                int yCoord = currentCorridor.startYPos;

                // Depending on the direction, add or subtract from the appropriate
                // coordinate based on how far through the length the loop is.
                switch (currentCorridor.direction)
                {
                    case Direction.North:
                        yCoord += j;
                        break;
                    case Direction.East:
                        xCoord += j;
                        break;
                    case Direction.South:
                        yCoord -= j;
                        break;
                    case Direction.West:
                        xCoord -= j;
                        break;
                }

                // Set the tile at these coordinates to Floor.
                tiles[xCoord][yCoord] = TileType.Floor;
            }
        }
    }


    void InstantiateTiles()
    {
        // Go through all the tiles in the jagged array...
        for (int i = 0; i < tiles.Length; i++)
        {
            for (int j = 0; j < tiles[i].Length; j++)
            {
                // ... and instantiate a floor tile for it.
                //InstantiateFromArray(floorTiles, i, j);
                TiledMapSol.SetTile(new Vector3Int(i, j, 1), floorTiles[0]);


                //print(new Vector3Int(i, j, 1));
               // print(floorTiles[0]);

                // If the tile type is Wall...
                if (tiles[i][j] == TileType.Wall)
                {
                    // ... instantiate a wall over the top.

                    TiledMapMur.SetTile(new Vector3Int(i,j,1), wallTiles[0]);

                    //InstantiateFromArray(wallTiles, i, j);
                }
            }
        }
    }


    void InstantiateOuterWalls()
    {
        // The outer walls are one unit left, right, up and down from the board.
        float leftEdgeX = -1f;
        float rightEdgeX = columns + 0f;
        float bottomEdgeY = -1f;
        float topEdgeY = rows + 0f;

        // Instantiate both vertical walls (one on each side).
        InstantiateVerticalOuterWall(leftEdgeX, bottomEdgeY, topEdgeY);
        InstantiateVerticalOuterWall(rightEdgeX, bottomEdgeY, topEdgeY);

        // Instantiate both horizontal walls, these are one in left and right from the outer walls.
        InstantiateHorizontalOuterWall(leftEdgeX + 1f, rightEdgeX - 1f, bottomEdgeY);
        InstantiateHorizontalOuterWall(leftEdgeX + 1f, rightEdgeX - 1f, topEdgeY);
    }


    void InstantiateVerticalOuterWall(float xCoord, float startingY, float endingY)
    {
        // Start the loop at the starting value for Y.
        float currentY = startingY;

        // While the value for Y is less than the end value...
        while (currentY <= endingY)
        {

            TiledMapMur.SetTile(new Vector3Int((int) xCoord, (int)currentY, 1), wallTiles[0]);
            // ... instantiate an outer wall tile at the x coordinate and the current y coordinate.
            //InstantiateFromArray(outerWallTiles, xCoord, currentY);

            currentY++;
        }
    }


    void InstantiateHorizontalOuterWall(float startingX, float endingX, float yCoord)
    {
        // Start the loop at the starting value for X.
        float currentX = startingX;

        // While the value for X is less than the end value...
        while (currentX <= endingX)
        {

            TiledMapMur.SetTile(new Vector3Int((int)currentX, (int)yCoord, 1), wallTiles[0]);
            // ... instantiate an outer wall tile at the y coordinate and the current x coordinate.
            //InstantiateFromArray(outerWallTiles, currentX, yCoord);

            currentX++;
        }
    }


    void InstantiateFromArray(GameObject[] prefabs, float xCoord, float yCoord)
    {
        // Create a random index for the array.
        int randomIndex = Random.Range(0, prefabs.Length);




        // The position to be instantiated at is based on the coordinates.
        Vector3 position = new Vector3(xCoord, yCoord, 0f);

        //TiledMap.SetTile(position, prefabs[randomIndex]);


        // Create an instance of the prefab from the random index of the array.
        GameObject tileInstance = Instantiate(prefabs[randomIndex], position, Quaternion.identity) as GameObject;

        tileInstance.transform.localScale = new Vector3(4, 4, 4);

        // Set the tile's parent to the board holder.
        tileInstance.transform.parent = boardHolder.transform;
    }
}