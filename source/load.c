#include <NEMain.h>
#include "main.h"
#include "load.h"


NE_Material* white_ceiling_tile002a, * white_floor_tile002a, * white_floor_tile002a_hd, * white_wall_tile003a, * white_wall_tile003a_hd, * white_wall_tile003c, * white_wall_tile003c_hd, * white_wall_tile003f, * white_wall_tile003f_hd, * black_floor_metal_001c, * black_floor_metal_001c_hd, * black_wall_metal_002a, * black_wall_metal_002a_hd, * black_wall_metal_002b, * black_wall_metal_002b_hd, * black_wall_metal_002c, * black_wall_metal_002c_hd, * Debug_Material, * debugempty;
NE_Palette* white_ceiling_tile002aPal, * white_floor_tile002aPal, * white_floor_tile002a_hdPal, * white_wall_tile003aPal, * white_wall_tile003a_hdPal, * white_wall_tile003cPal, * white_wall_tile003c_hdPal, * white_wall_tile003fPal, * white_wall_tile003f_hdPal, * black_floor_metal_001cPal, * black_floor_metal_001c_hdPal, * black_wall_metal_002aPal, * black_wall_metal_002a_hdPal, * black_wall_metal_002bPal, * black_wall_metal_002b_hdPal, * black_wall_metal_002cPal, * black_wall_metal_002c_hdPal;
//for when you can create multiple texture usig one pallete
//NE_Palette* tile_cleanPal16, * metal_cleanPal16;



// load textures
// @param textureMode   0 = Low Resolution but many diffrent textures
//                      1 = TODO High Resolution but more tepeating textures
//                      2 = TODO Portal 1 Textures
void LoadPal16(NE_Material* material, void* texturelBin, NE_Palette* palette, void* paletteBin, int resolution)
{
    NE_MaterialTexLoad(material, NE_PAL16, resolution, resolution, NE_TEXTURE_WRAP_S | NE_TEXTURE_WRAP_T, texturelBin);
    NE_PaletteLoad(palette, paletteBin, 16, NE_PAL16);
    NE_MaterialSetPalette(material, palette);
}


void LoadTextures(int textureMode)
{
    white_ceiling_tile002a = NE_MaterialCreate();
    white_floor_tile002a = NE_MaterialCreate();
    white_wall_tile003a = NE_MaterialCreate();
    white_wall_tile003c = NE_MaterialCreate();
    white_wall_tile003f = NE_MaterialCreate();
    black_floor_metal_001c = NE_MaterialCreate();
    black_wall_metal_002a = NE_MaterialCreate();
    black_wall_metal_002b = NE_MaterialCreate();
    black_wall_metal_002c = NE_MaterialCreate();

    //for when you can create multiple texture usig one pallete
    //tile_cleanPal16 = NE_PaletteCreate();
    //metal_cleanPal16 = NE_PaletteCreate();

    white_ceiling_tile002aPal = NE_PaletteCreate();
    white_floor_tile002aPal = NE_PaletteCreate();
    white_wall_tile003aPal = NE_PaletteCreate();
    white_wall_tile003cPal = NE_PaletteCreate();
    white_wall_tile003fPal = NE_PaletteCreate();
    black_floor_metal_001cPal = NE_PaletteCreate();
    black_wall_metal_002aPal = NE_PaletteCreate();
    black_wall_metal_002bPal = NE_PaletteCreate();
    black_wall_metal_002cPal = NE_PaletteCreate();

    if (textureMode == 0)
    {
        LoadPal16(white_ceiling_tile002a, (u8*)white_ceiling_tile002a_tex_bin, white_ceiling_tile002aPal, (void*)white_ceiling_tile002a_pal_bin, 256);

        LoadPal16(white_floor_tile002a, (u8*)white_floor_tile002a_tex_bin, white_floor_tile002aPal, (void*)white_floor_tile002a_pal_bin, 256);

        LoadPal16(white_wall_tile003a, (u8*)white_wall_tile003a_tex_bin, white_wall_tile003aPal, (void*)white_wall_tile003a_pal_bin, 128);

        LoadPal16(white_wall_tile003c, (u8*)white_wall_tile003c_tex_bin, white_wall_tile003cPal, (void*)white_wall_tile003c_pal_bin, 128);

        LoadPal16(white_wall_tile003f, (u8*)white_wall_tile003f_tex_bin, white_wall_tile003fPal, (void*)white_wall_tile003f_pal_bin, 128);

        LoadPal16(black_floor_metal_001c, (u8*)black_floor_metal_001c_tex_bin, black_floor_metal_001cPal, (void*)black_floor_metal_001c_pal_bin, 128);

        LoadPal16(black_wall_metal_002a, (u8*)black_wall_metal_002a_tex_bin, black_wall_metal_002aPal, (void*)black_wall_metal_002a_pal_bin, 256);

        LoadPal16(black_wall_metal_002b, (u8*)black_wall_metal_002b_tex_bin, black_wall_metal_002bPal, (void*)black_wall_metal_002b_pal_bin, 256);

        LoadPal16(black_wall_metal_002c, (u8*)black_wall_metal_002c_tex_bin, black_wall_metal_002cPal, (void*)black_wall_metal_002c_pal_bin, 256);
    }
    if (textureMode == 1) 
    {
        LoadPal16(white_ceiling_tile002a, (u8*)white_floor_tile002a_hd_tex_bin, white_floor_tile002aPal, (void*)white_floor_tile002a_hd_pal_bin, 256);

        LoadPal16(white_floor_tile002a, (u8*)white_floor_tile002a_hd_tex_bin, white_floor_tile002aPal, (void*)white_floor_tile002a_hd_pal_bin, 512);

        LoadPal16(white_wall_tile003a, (u8*)white_wall_tile003a_hd_tex_bin, white_wall_tile003aPal, (void*)white_wall_tile003a_hd_pal_bin, 256);

        LoadPal16(black_floor_metal_001c, (u8*)black_floor_metal_001c_hd_tex_bin, black_floor_metal_001cPal, (void*)black_floor_metal_001c_hd_pal_bin, 256);

        LoadPal16(black_wall_metal_002c, (u8*)black_wall_metal_002c_hd_tex_bin, black_wall_metal_002cPal, (void*)black_wall_metal_002c_hd_pal_bin, 512);
    }
    Debug_Material = NE_MaterialCreate();
    debugempty = NE_MaterialCreate();

    NE_MaterialTexLoad(Debug_Material, NE_A1RGB5, 128, 128, NE_TEXTURE_WRAP_S | NE_TEXTURE_WRAP_T,
        (u8*)Debug_tex_bin);

    NE_MaterialTexLoad(debugempty, NE_A1RGB5, 64, 64, NE_TEXTURE_WRAP_S | NE_TEXTURE_WRAP_T,
        (u8*)debugempty_tex_bin);
}

//Render all Planes in the level
void RenderPlanes(Level level) {
    int i;
    for (i = 0; i < 500; i++)
    {
        // Render a plane
        NE_PolyFormat(31, 1, NE_LIGHT_0, NE_CULL_BACK, 0);

        NE_MaterialUse(level.Plane[i].material);

        NE_PolyBegin(GL_QUAD);
        //NE_PolyNormal(level.Plane[i].nx / 100, level.Plane[i].nz / 100, level.Plane[i].ny / 100);

        NE_PolyTexCoord(level.Plane[i].v0, level.Plane[i].u1);
        NE_PolyVertex(level.Plane[i].vertex1.y / 100, level.Plane[i].vertex1.z / 100, level.Plane[i].vertex1.x / 100);

        NE_PolyTexCoord(level.Plane[i].v0, level.Plane[i].u0);
        NE_PolyVertex(level.Plane[i].vertex4.y / 100, level.Plane[i].vertex4.z / 100, level.Plane[i].vertex4.x / 100);

        NE_PolyTexCoord(level.Plane[i].v1, level.Plane[i].u0);
        NE_PolyVertex(level.Plane[i].vertex3.y / 100, level.Plane[i].vertex3.z / 100, level.Plane[i].vertex3.x / 100);

        NE_PolyTexCoord(level.Plane[i].v1, level.Plane[i].u1);
        NE_PolyVertex(level.Plane[i].vertex2.y / 100, level.Plane[i].vertex2.z / 100, level.Plane[i].vertex2.x / 100);

        NE_PolyEnd();
    }
}

void RenderPlanesManual(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, double u, double v, NE_Material* Material, int Zone, int id) {
    int u0 = 0;
    int v0 = 0;
    int u1 = 0;
    int v1 = 0;
    //float nx = 0;
    //float ny = 0;
    //float nz = 0;
    float x4 = 0;
    float y4 = 0;
    float z4 = 0;

    if (z1 == z3) {  //look if side is floor
        //create vertex x4/y4/z4
        x4 = x3;
        y4 = y1;
        z4 = z2;
        //create texture coordinates
        if (textureMode == 0) {
            u0 = 0;
            v0 = 0;
            u1 = 1 * (x3 - x2) * u * 4;
            v1 = 1 * (y2 - y1) * v * 4;
        }
        if (textureMode == 1) {
            u0 = 0;
            v0 = 0;
            u1 = 2 * (x3 - x2) * u * 4;
            v1 = 2 * (y2 - y1) * v * 4;
        }
        if (x2 == x3) { //look if side cieling
            //create vertex x4/y4/z4
            x4 = x1;
            y4 = y3;
            z4 = z2;
            //create texture coordinates
            if (textureMode == 0) {
                u0 = 0;
                v0 = 0;
                u1 = 1 * (y2 - y3) * u * 4;
                v1 = 1 * (x1 - x2) * v * 4;
            }
            if (textureMode == 1) {
                u0 = 0;
                v0 = 0;
                u1 = 2 * (y2 - y3) * u * 4;
                v1 = 2 * (x1 - x2) * v * 4;
            }
        }
    }

    else if (y1 == y2) {  //look if side is y aligned wall and create vertex x4/y4/z4
        //create vertex x4/y4/z4
        x4 = x1;
        y4 = y3;
        z4 = z3;
        //create texture coordinates
        if (textureMode == 0) {
            u0 = 0;
            v0 = 0;
            u1 = 1 * (z3 - z1) * u * 4;
            v1 = 1 * (x2 - x1) * v * 4;
        }
        if (textureMode == 1) {
            u0 = 0;
            v0 = 0;
            u1 = 2 * (z3 - z1) * u * 4;
            v1 = 2 * (x2 - x1) * v * 4;
        }
        //nx = x2 + 1;
        //ny = y2;
        //nz = z2 - z3;

    }
    else if (x2 == x3) {  //else side is x aligned wall, create vertex x4
        //create vertex x4/y4/z4
        x4 = x3;
        y4 = y1;
        z4 = z3;
        //create texture coordinates
        if (textureMode == 0) {
            u0 = 0;
            v0 = 0;
            u1 = 1 * (z3 - z1) * u * 4;
            v1 = 1 * (y2 - y1) * v * 4;
        }
        if (textureMode == 1) {
            u0 = 0;
            v0 = 0;
            u1 = 2 * (z3 - z1) * u * 4;
            v1 = 2 * (y2 - y1) * v * 4;
        }
    }


    // Create a block side
    NE_PolyFormat(31, 1, NE_LIGHT_0, NE_CULL_BACK, 0);

    NE_MaterialUse(Material);

    NE_PolyBegin(GL_QUAD);
    //NE_PolyNormal(nx / 100, nz / 100, ny / 100);

    NE_PolyTexCoord(v0, u1);
    NE_PolyVertex(y1 / 100, z1 / 100, x1 / 100);

    NE_PolyTexCoord(v1, u1);
    NE_PolyVertex(y2 / 100, z2 / 100, x2 / 100);

    NE_PolyTexCoord(v1, u0);
    NE_PolyVertex(y3 / 100, z3 / 100, x3 / 100);

    NE_PolyTexCoord(v0, u0);
    NE_PolyVertex(y4 / 100, z4 / 100, x4 / 100);

    NE_PolyEnd();

    //block->Model = NE_ModelCreate(NE_Static);
    //block->Physics = NE_PhysicsCreate(NE_BoundingBox);
    //NE_ModelLoadStaticMesh(block->Model, (u32*)plane_bin);
    //NE_PhysicsSetSize(block->Physics, x1 + x2, -y1 + y2, z2 - z3);    //collision anwenden

    //NE_PhysicsSetModel(block->Physics, // Physics object
    //    (void*)block->Model); // Model assigned to it

    //NE_PhysicsEnable(block->Physics, false);
}

void loadSave() {
    FILE* savefile;
    savefile = fopen("fat:/_nds/PortalDS/save.sav", "rb");
    while (1)
    {
        char word[128];
        int res = fscanf(savefile, "%s", word);
        if (res == EOF) {
            break; // EOF = End Of File. Quit the loop.
        }
        if (strcmp(word, "test") == 0) // Read
        {
            fscanf(savefile, "%s", word);
            printf("\x1b[9;1Hx1:%s", word);
        }
    }
    fclose(savefile);
}

// loads a .vmf file
int loadLevel() {
    char* levelName = level.name;
    FILE* levelFile;
    PLANE tempPlane;
    char* location = "fat:/_nds/PortalDS/levels/";
    char* extension = ".vmf";
    char fileLocation[strlen(location) + strlen(levelName) + strlen(extension) + 1];
    snprintf(fileLocation, sizeof(fileLocation), "%s%s%s", location, levelName, extension);
    levelFile = fopen(fileLocation, "rb");
    int i = 0;
    //Plane = (PLANE*)malloc(n * sizeof(PLANE));
    ////Plane = malloc(n * sizeof(PLANE));
    while (1)
    {
        //for (i = 0; i < n; i++)
        //{
            char word[256];
            //tempPlane = (PLANE*)malloc(sizeof(PLANE));
            int res = fscanf(levelFile, "%s", word);
            tempPlane.isDrawn = 1;
            if (res == EOF) {
                break; // EOF = End Of File. Quit the loop.
            }
            if (strcmp(word, "side") == 0) // Read block
            {
                char pId[3];
                char tempx1[6], tempy1[6], tempz1[6];
                char tempx2[6], tempy2[6], tempz2[6];
                char tempx3[6], tempy3[6], tempz3[6];
                char tempMaterial[30];
                fscanf(levelFile, "%*s%*11c%3s", pId);
                int planeId = (float)atof(pId);
                if (planeId < 100) // when the id is 3 numbers long it changes when the coords begin
                {
                    fscanf(levelFile, "%*s%*2c(%s %s %s)", tempx1, tempy1, tempz1);
                }
                else 
                {
                    fscanf(levelFile, "%*s%*7s%*2c(%s %s %s)", tempx1, tempy1, tempz1);
                }
                fscanf(levelFile, " (%s %s %s)", tempx2, tempy2, tempz2);
                fscanf(levelFile, " (%s %s %s)", tempx3, tempy3, tempz3);
                fscanf(levelFile, "%*s%*[^/]/%[^\"]", tempMaterial);
                float x1 = (float)atof(tempx1);
                float y1 = (float)atof(tempy1);
                float z1 = (float)atof(tempz1);
                float x2 = (float)atof(tempx2);
                float y2 = (float)atof(tempy2);
                float z2 = (float)atof(tempz2);
                float x3 = (float)atof(tempx3);
                float y3 = (float)atof(tempy3);
                float z3 = (float)atof(tempz3);
                tempPlane.id = planeId;
                tempPlane.vertex1.x = x1;
                tempPlane.vertex1.y = y1;
                tempPlane.vertex1.z = z1;
                tempPlane.vertex2.x = x2;
                tempPlane.vertex2.y = y2;
                tempPlane.vertex2.z = z2;
                tempPlane.vertex3.x = x3;
                tempPlane.vertex3.y = y3;
                tempPlane.vertex3.z = z3;
                if (strcmp(tempMaterial, "WHITE_CEILING_TILE002A") == 0)
                    tempPlane.material = white_ceiling_tile002a;
                else if (strcmp(tempMaterial, "WHITE_FLOOR_TILE002A") == 0)
                    tempPlane.material = white_floor_tile002a;
                else if (strcmp(tempMaterial, "WHITE_WALL_TILE003A") == 0)
                    tempPlane.material = white_wall_tile003a;
                else if (strcmp(tempMaterial, "WHITE_WALL_TILE003C") == 0)
                    tempPlane.material = white_wall_tile003c;
                else if (strcmp(tempMaterial, "WHITE_WALL_TILE003F") == 0)
                    tempPlane.material = white_wall_tile003f;
                else if (strcmp(tempMaterial, "BLACK_FLOOR_METAL_001C") == 0)
                    tempPlane.material = black_floor_metal_001c;
                else if (strcmp(tempMaterial, "BLACK_WALL_METAL_002A") == 0)
                    tempPlane.material = black_wall_metal_002a;
                else if (strcmp(tempMaterial, "BLACK_WALL_METAL_002B") == 0)
                    tempPlane.material = black_wall_metal_002b;
                else if (strcmp(tempMaterial, "BLACK_WALL_METAL_002C") == 0)
                    tempPlane.material = black_wall_metal_002c;
                else if (strcmp(tempMaterial, "TOOLSNODRAW") == 0)
                    tempPlane.isDrawn = 0;
                else
                    tempPlane.material = debugempty;

                if (tempPlane.isDrawn) {
                    level.Plane[i].vertex1 = tempPlane.vertex1;
                    level.Plane[i].vertex2 = tempPlane.vertex2;
                    level.Plane[i].vertex3 = tempPlane.vertex3;
                    level.Plane[i].material = tempPlane.material;
                }


                //calculate vertex 4 and textures
                float u = 0.25;
                float v = 0.25;
                level.Plane[i].u0 = 0;
                level.Plane[i].v0 = 0;
                level.Plane[i].u1 = 0;
                level.Plane[i].v1 = 0;

                if (level.Plane[i].vertex1.z == level.Plane[i].vertex3.z) {  //look if side is floor
                    //create vertex x4/y4/z4
                    level.Plane[i].vertex4.y = level.Plane[i].vertex3.y;
                    level.Plane[i].vertex4.x = level.Plane[i].vertex1.x;
                    level.Plane[i].vertex4.z = level.Plane[i].vertex2.z;
                    //create texture coordinates
                    if (textureMode == 0) {
                        level.Plane[i].u0 = 0;
                        level.Plane[i].v0 = 0;
                        level.Plane[i].u1 = 1 * (level.Plane[i].vertex3.y - level.Plane[i].vertex2.y) * u * 4;
                        level.Plane[i].v1 = 1 * (level.Plane[i].vertex2.x - level.Plane[i].vertex1.x) * v * 4;
                    }
                    if (textureMode == 1) {
                        level.Plane[i].u0 = 0;
                        level.Plane[i].v0 = 0;
                        level.Plane[i].u1 = 2 * (level.Plane[i].vertex3.y - level.Plane[i].vertex2.y) * u * 4;
                        level.Plane[i].v1 = 2 * (level.Plane[i].vertex2.x - level.Plane[i].vertex1.x) * v * 4;
                    }
                    if (level.Plane[i].vertex2.y == level.Plane[i].vertex3.y) { //look if side cieling
                        //create vertex x4/y4/z4
                        level.Plane[i].vertex4.y = level.Plane[i].vertex1.y;
                        level.Plane[i].vertex4.x = level.Plane[i].vertex3.x;
                        level.Plane[i].vertex4.z = level.Plane[i].vertex2.z;
                        //create texture coordinates
                        if (textureMode == 0) {
                            level.Plane[i].u0 = 0;
                            level.Plane[i].v0 = 0;
                            level.Plane[i].u1 = 1 * (level.Plane[i].vertex2.x - level.Plane[i].vertex3.x) * u * 4;
                            level.Plane[i].v1 = 1 * (level.Plane[i].vertex1.y - level.Plane[i].vertex2.y) * v * 4;
                        }
                        if (textureMode == 1) {
                            level.Plane[i].u0 = 0;
                            level.Plane[i].v0 = 0;
                            level.Plane[i].u1 = 2 * (level.Plane[i].vertex2.x - level.Plane[i].vertex3.x) * u * 4;
                            level.Plane[i].v1 = 2 * (level.Plane[i].vertex1.y - level.Plane[i].vertex2.y) * v * 4;
                        }
                    }
                }

                else if (level.Plane[i].vertex1.x == level.Plane[i].vertex2.x) {  //look if side is y aligned wall and create vertex x4/y4/z4
                    //create vertex x4/y4/z4
                    level.Plane[i].vertex4.y = level.Plane[i].vertex1.y;
                    level.Plane[i].vertex4.x = level.Plane[i].vertex3.x;
                    level.Plane[i].vertex4.z = level.Plane[i].vertex3.z;
                    //level.Plane[i].nx = level.Plane[i].vertex2.x + 128;
                    //level.Plane[i].ny = level.Plane[i].vertex2.y;
                    //level.Plane[i].nz = (level.Plane[i].vertex2.z - level.Plane[i].vertex3.z) / 2;
                    //create texture coordinates
                    if (textureMode == 0) {
                        level.Plane[i].u0 = 0;
                        level.Plane[i].v0 = 0;
                        level.Plane[i].u1 = 1 * (level.Plane[i].vertex3.z - level.Plane[i].vertex1.z) * u * 4;
                        level.Plane[i].v1 = 1 * (level.Plane[i].vertex2.y - level.Plane[i].vertex1.y) * v * 4;
                    }
                    else if (textureMode == 1) {
                        level.Plane[i].u0 = 0;
                        level.Plane[i].v0 = 0;
                        level.Plane[i].u1 = 2 * (level.Plane[i].vertex3.z - level.Plane[i].vertex1.z) * u * 4;
                        level.Plane[i].v1 = 2 * (level.Plane[i].vertex2.y - level.Plane[i].vertex1.y) * v * 4;
                    }
                }
                else if (level.Plane[i].vertex2.y == level.Plane[i].vertex3.y) {  //else side is x aligned wall, create vertex x4
                    //create vertex x4/y4/z4
                    level.Plane[i].vertex4.y = level.Plane[i].vertex3.y;
                    level.Plane[i].vertex4.x = level.Plane[i].vertex1.x;
                    level.Plane[i].vertex4.z = level.Plane[i].vertex3.z;
                    //create texture coordinates
                    if (textureMode == 0) {
                        level.Plane[i].u0 = 0;
                        level.Plane[i].v0 = 0;
                        level.Plane[i].u1 = 1 * (level.Plane[i].vertex3.z - level.Plane[i].vertex1.z) * u * 4;
                        level.Plane[i].v1 = 1 * (level.Plane[i].vertex2.x - level.Plane[i].vertex1.x) * v * 4;
                    }
                    else if (textureMode == 1) {
                        level.Plane[i].u0 = 0;
                        level.Plane[i].v0 = 0;
                        level.Plane[i].u1 = 2 * (level.Plane[i].vertex3.z - level.Plane[i].vertex1.z) * u * 4;
                        level.Plane[i].v1 = 2 * (level.Plane[i].vertex2.x - level.Plane[i].vertex1.x) * v * 4;
                    }
                }

                //if (Plane->isDrawn)
                    //printf("\nplane id:%d\nmaterial:%s\nx1:%.0f x2:%.0f x3:%.0f\ny1:%.0f y2:%.0f y3:%.0f\nz1:%.0f z2:%.0f z3:%.0f\n", Plane->id, tempMaterial, Plane->vertex1.x, Plane->vertex1.y, Plane->vertex1.z, Plane->vertex2.x, Plane->vertex2.y, Plane->vertex2.z, Plane->vertex3.x, Plane->vertex3.y, Plane->vertex3.z);
                //printf("id:%d\tx1:%.0f\n", (Plane + i)->id, (Plane + i)->vertex1.x);
                i++;
                //break;
            }
            //printf("%s", tempy1);
        //}
    }
    if (i >= MAX_PLANES)
        printf("Warning max Planes reached:");

    fclose(levelFile);
    //RenderPlanes(level);
    //free(tempPlane);
    return 0;
}
