#include <NEMain.h>
#include "assets.h"
#include "main.h"
#include "load.h"
#include "physics.h"


//Models
NE_Model* debug_vision_model, *portal_orange_model, *portal_blue_model;

//Animated models
NE_Model *w_portalgun_model;

//Animations
NE_Animation *w_portalgun_fire1_animation;

//Model textues
NE_Material *w_portalgun_tex, *portal_orange_tex, *portal_blue_tex;
NE_Palette *w_portalgun_pal, *portal_orange_pal, *portal_blue_pal;

//Map textures
NE_Material* white_ceiling_tile002a, * white_floor_tile002a, * white_floor_tile002a_hd, * white_wall_tile003a, * white_wall_tile003a_hd, * white_wall_tile003c, * white_wall_tile003c_hd, * white_wall_tile003f, * white_wall_tile003f_hd, * black_floor_metal_001c, * black_floor_metal_001c_hd, * black_wall_metal_002a, * black_wall_metal_002a_hd, * black_wall_metal_002b, * black_wall_metal_002b_hd, * black_wall_metal_002c, * black_wall_metal_002c_hd, * Debug_Material, * debugempty;
NE_Palette* white_ceiling_tile002aPal, * white_floor_tile002aPal, * white_floor_tile002a_hdPal, * white_wall_tile003aPal, * white_wall_tile003a_hdPal, * white_wall_tile003cPal, * white_wall_tile003c_hdPal, * white_wall_tile003fPal, * white_wall_tile003f_hdPal, * black_floor_metal_001cPal, * black_floor_metal_001c_hdPal, * black_wall_metal_002aPal, * black_wall_metal_002a_hdPal, * black_wall_metal_002bPal, * black_wall_metal_002b_hdPal, * black_wall_metal_002cPal, * black_wall_metal_002c_hdPal;
//for when you can create multiple texture usig one pallete
//NE_Palette* tile_cleanPal16, * metal_cleanPal16;



void LoadPal16(NE_Material* material, void* texturelBin, NE_Palette* palette, void* paletteBin, int resolution)
{
    NE_MaterialTexLoad(material, NE_PAL16, resolution, resolution, NE_TEXTURE_WRAP_S | NE_TEXTURE_WRAP_T, texturelBin);
    NE_PaletteLoad(palette, paletteBin, 16, NE_PAL16);
    NE_MaterialSetPalette(material, palette);
}
void LoadPal4(NE_Material* material, void* texturelBin, NE_Palette* palette, void* paletteBin, int resolution)
{
    NE_MaterialTexLoad(material, NE_PAL4, resolution, resolution, NE_TEXTURE_WRAP_S | NE_TEXTURE_WRAP_T, texturelBin);
    NE_PaletteLoad(palette, paletteBin, 4, NE_PAL4);
    NE_MaterialSetPalette(material, palette);
}
//Pal4 but only 2 colors used
void LoadPal2(NE_Material* material, void* texturelBin, NE_Palette* palette, void* paletteBin, int resolution)
{
    NE_MaterialTexLoad(material, NE_PAL4, resolution, resolution, NE_TEXTURE_WRAP_S | NE_TEXTURE_WRAP_T, texturelBin);
    NE_PaletteLoad(palette, paletteBin, 2, NE_PAL4);
    NE_MaterialSetPalette(material, palette);
}
//1:2 aspect ratio
void LoadPal4_1_2(NE_Material* material, void* texturelBin, NE_Palette* palette, void* paletteBin, int resolution)
{
    NE_MaterialTexLoad(material, NE_PAL4, resolution / 2, resolution, NE_TEXTURE_WRAP_S | NE_TEXTURE_WRAP_T, texturelBin);
    NE_PaletteLoad(palette, paletteBin, 4, NE_PAL4);
    NE_MaterialSetPalette(material, palette);
}


// load textures
// @param textureMode   0 = Low Resolution but many diffrent textures
//                      1 = TODO High Resolution but more tepeating textures
//                      2 = TODO Portal 1 Textures
void LoadTextures()
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
        LoadPal2(white_ceiling_tile002a, (u8*)white_ceiling_tile002a_tex_bin, white_ceiling_tile002aPal, (void*)white_ceiling_tile002a_pal_bin, 64);

        LoadPal4(white_floor_tile002a, (u8*)white_floor_tile002a_tex_bin, white_floor_tile002aPal, (void*)white_floor_tile002a_pal_bin, 64);

        LoadPal4_1_2(white_wall_tile003a, (u8*)white_wall_tile003a_tex_bin, white_wall_tile003aPal, (void*)white_wall_tile003a_pal_bin, 64);

        LoadPal4(white_wall_tile003c, (u8*)white_wall_tile003c_tex_bin, white_wall_tile003cPal, (void*)white_wall_tile003c_pal_bin, 64);

        LoadPal4(white_wall_tile003f, (u8*)white_wall_tile003f_tex_bin, white_wall_tile003fPal, (void*)white_wall_tile003f_pal_bin, 32);

        LoadPal4(black_floor_metal_001c, (u8*)black_floor_metal_001c_tex_bin, black_floor_metal_001cPal, (void*)black_floor_metal_001c_pal_bin, 64);

        LoadPal16(black_wall_metal_002a, (u8*)black_wall_metal_002a_tex_bin, black_wall_metal_002aPal, (void*)black_wall_metal_002a_pal_bin, 256);

        LoadPal16(black_wall_metal_002b, (u8*)black_wall_metal_002b_tex_bin, black_wall_metal_002bPal, (void*)black_wall_metal_002b_pal_bin, 256);

        LoadPal16(black_wall_metal_002c, (u8*)black_wall_metal_002c_tex_bin, black_wall_metal_002cPal, (void*)black_wall_metal_002c_pal_bin, 256);
    }
    else if (textureMode == 1) 
    {
        LoadPal16(white_floor_tile002a, (u8*)white_floor_tile002a_hd_tex_bin, white_floor_tile002aPal, (void*)white_floor_tile002a_hd_pal_bin, 512);

        LoadPal16(white_wall_tile003a, (u8*)white_wall_tile003a_hd_tex_bin, white_wall_tile003aPal, (void*)white_wall_tile003a_hd_pal_bin, 256);

        LoadPal16(black_floor_metal_001c, (u8*)black_floor_metal_001c_hd_tex_bin, black_floor_metal_001cPal, (void*)black_floor_metal_001c_hd_pal_bin, 256);

        LoadPal16(black_wall_metal_002a, (u8*)black_wall_metal_002a_hd_tex_bin, black_wall_metal_002aPal, (void*)black_wall_metal_002a_hd_pal_bin, 512);

    }
    Debug_Material = NE_MaterialCreate();
    debugempty = NE_MaterialCreate();
    w_portalgun_tex = NE_MaterialCreate();
    w_portalgun_pal = NE_PaletteCreate();
    portal_orange_tex = NE_MaterialCreate();
    portal_orange_pal = NE_PaletteCreate();
    portal_blue_tex = NE_MaterialCreate();
    portal_blue_pal = NE_PaletteCreate();

    NE_MaterialTexLoad(w_portalgun_tex, NE_PAL16, 128, 128, NE_TEXTURE_WRAP_S | NE_TEXTURE_WRAP_T, (u8*)w_portalgun_tex_bin);
    NE_PaletteLoad(w_portalgun_pal, (void*)w_portalgun_pal_bin, 16, NE_PAL16);
    NE_MaterialSetPalette(w_portalgun_tex, w_portalgun_pal);

    LoadPal4_1_2(portal_orange_tex, (u8*)portal_orange_tex_bin, portal_orange_pal, (void*)portal_orange_pal_bin, 64);
    LoadPal4_1_2(portal_blue_tex, (u8*)portal_blue_tex_bin, portal_blue_pal, (void*)portal_blue_pal_bin, 64);

    //transparent
    //NE_MaterialTexLoad(portal_orange_tex, NE_PAL4, 32, 64, NE_TEXTURE_WRAP_S | NE_TEXTURE_WRAP_T | NE_TEXTURE_COLOR0_TRANSPARENT, (u8*)portal_orange_tex_bin);
    //NE_PaletteLoad(portal_orange_pal, (void*)portal_orange_pal_bin, 2, NE_PAL4);
    //NE_MaterialSetPalette(portal_orange_tex, portal_orange_pal);
    //NE_MaterialTexLoad(portal_blue_tex, NE_PAL4, 32, 64, NE_TEXTURE_WRAP_S | NE_TEXTURE_WRAP_T | NE_TEXTURE_COLOR0_TRANSPARENT, (u8*)portal_blue_tex_bin);
    //NE_PaletteLoad(portal_blue_pal, (void*)portal_blue_pal_bin, 2, NE_PAL4);
    //NE_MaterialSetPalette(portal_blue_tex, portal_blue_pal);

    NE_MaterialTexLoad(Debug_Material, NE_A1RGB5, 128, 128, NE_TEXTURE_WRAP_S | NE_TEXTURE_WRAP_T, (u8*)Debug_tex_bin);

    NE_MaterialTexLoad(debugempty, NE_A1RGB5, 64, 64, NE_TEXTURE_WRAP_S | NE_TEXTURE_WRAP_T, (u8*)debugempty_tex_bin);
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
int loadLevelVmf(char* levelName) {
    FILE* levelFile;
    PLANE tempPlane;
    char* location = "fat:/_nds/PortalDS/levels/";
    char* extension = ".vmf";
    char fileLocation[strlen(location) + strlen(levelName) + strlen(extension) + 1];
    snprintf(fileLocation, sizeof(fileLocation), "%s%s%s", location, levelName, extension);
    if ((levelFile = fopen(fileLocation, "rb")) == NULL) {
        location = "nitro:/levels/";
        snprintf(fileLocation, sizeof(fileLocation), "%s%s%s", location, levelName, extension);
        levelFile = fopen(fileLocation, "rb");
    }
    int i = 0;
    //Plane = (PLANE*)malloc(n * sizeof(PLANE));
    ////Plane = malloc(n * sizeof(PLANE));
    while (1)
    {
        char word[256];
        //tempPlane = (PLANE*)malloc(sizeof(PLANE));
        int res = fscanf(levelFile, "%s", word);
        tempPlane.isDrawn = 1;
        if (res == EOF) {
            break; // EOF = End Of File. Quit the loop.
        }
        if (strcmp(word, "side") == 0) // Read block
        {
            //temporary values (overwritten with evry net object)
            char id[3];
            char tempx1[10], tempy1[10], tempz1[10];
            char tempx2[10], tempy2[10], tempz2[10];
            char tempx3[10], tempy3[10], tempz3[10];
            char tempMaterial[30];
            char tempuaxis[6], tempuscale[6];
            char tempvaxis[6], tempvscale[6];
            fscanf(levelFile, "%*s%*11c%3s%*[\"]", id); //search for the start of the data
            fscanf(levelFile, "%*s%*c\"(%s %s %s)", tempx1, tempy1, tempz1);    //read file values into temporary values
            fscanf(levelFile, " (%s %s %s)", tempx2, tempy2, tempz2);
            fscanf(levelFile, " (%s %s %s)", tempx3, tempy3, tempz3);
            fscanf(levelFile, "%*s%*[^/]/%[^\"]", tempMaterial);
            fscanf(levelFile, "%*s%*s%*s%*s%*s %[^]]] %[^\"]", tempuaxis, tempuscale);
            fscanf(levelFile, "%*s%*s%*s%*s%*s %[^]]] %[^\"]", tempvaxis, tempvscale);
            int planeId = (float)atof(id); //unused
            tempPlane.vertex1.x = (float)atof(tempx1) * LEVEL_SIZE;
            tempPlane.vertex1.y = (float)atof(tempy1) * LEVEL_SIZE;
            tempPlane.vertex1.z = (float)atof(tempz1) * LEVEL_SIZE;
            tempPlane.vertex2.x = (float)atof(tempx2) * LEVEL_SIZE;
            tempPlane.vertex2.y = (float)atof(tempy2) * LEVEL_SIZE;
            tempPlane.vertex2.z = (float)atof(tempz2) * LEVEL_SIZE;
            tempPlane.vertex3.x = (float)atof(tempx3) * LEVEL_SIZE;
            tempPlane.vertex3.y = (float)atof(tempy3) * LEVEL_SIZE;
            tempPlane.vertex3.z = (float)atof(tempz3) * LEVEL_SIZE;
            float uaxis = (float)atof(tempuaxis);
            float uscale = (float)atof(tempuscale);
            float vaxis = (float)atof(tempvaxis);
            float vscale = (float)atof(tempvscale);

            //convert string material names to materials used in LoadTextures
            if (strcmp(tempMaterial, "WHITE_CEILING_TILE002A") == 0) {
                tempPlane.material = white_ceiling_tile002a;
            }
            else if (strcmp(tempMaterial, "WHITE_FLOOR_TILE002A") == 0) {
                tempPlane.material = white_floor_tile002a;
            }
            else if (strcmp(tempMaterial, "WHITE_WALL_TILE003A") == 0) {
                tempPlane.material = white_wall_tile003a;
            }
            else if (strcmp(tempMaterial, "WHITE_WALL_TILE003C") == 0) {
                tempPlane.material = white_wall_tile003c;
            }
            else if (strcmp(tempMaterial, "WHITE_WALL_TILE003F") == 0) {
                tempPlane.material = white_wall_tile003f;
            }
            else if (strcmp(tempMaterial, "BLACK_FLOOR_METAL_001C") == 0) {
                tempPlane.material = black_floor_metal_001c;
            }
            else if (strcmp(tempMaterial, "BLACK_WALL_METAL_002A") == 0) {
                tempPlane.material = black_wall_metal_002a;
            }
            else if (strcmp(tempMaterial, "BLACK_WALL_METAL_002B") == 0) {
                tempPlane.material = black_wall_metal_002b;
            }
            else if (strcmp(tempMaterial, "BLACK_WALL_METAL_002C") == 0) {
                tempPlane.material = black_wall_metal_002c;
            }
            else if (strcmp(tempMaterial, "TOOLSNODRAW") == 0)
                tempPlane.isDrawn = 0;
                //if material not recognized use debug texture
            else {
                tempPlane.material = debugempty;
                if (i >= 3000)
                    break;
                //tempPlane.isDrawn = 0;
            }

            //override for hd textures
            if (textureMode == 1)
            {
                if (strcmp(tempMaterial, "WHITE_CEILING_TILE002A") == 0)
                    tempPlane.material = white_floor_tile002a;
                else if (strcmp(tempMaterial, "WHITE_WALL_TILE003C") == 0)
                    tempPlane.material = white_wall_tile003a;
                else if (strcmp(tempMaterial, "WHITE_WALL_TILE003F") == 0)
                    tempPlane.material = white_wall_tile003a;
                else if (strcmp(tempMaterial, "BLACK_WALL_METAL_002B") == 0)
                    tempPlane.material = black_wall_metal_002a;
                else if (strcmp(tempMaterial, "BLACK_WALL_METAL_002C") == 0)
                    tempPlane.material = black_wall_metal_002a;
            }


            if (tempPlane.isDrawn) {


                //calculate vertex 4 and textures
                tempPlane.x0 = 0;
                tempPlane.y0 = 0;
                tempPlane.x1 = 0;
                tempPlane.y1 = 0;
                bool collisionsAlreadySet = false;
                //get texture size and adjust it (for diffent resolutions)
                int tempTextureFactorMultiply = 0;
                int tempTextureFactorDivide = 0;
                int textureSizeY = NE_TextureGetSizeY(tempPlane.material);
                if (textureSizeY == 32) {
                    tempTextureFactorMultiply = 1;
                    tempTextureFactorDivide = 8;
                }
                if (textureSizeY == 64) {
                    tempTextureFactorMultiply = 2;
                    tempTextureFactorDivide = 8;
                }
                else if (textureSizeY == 128) {
                    tempTextureFactorMultiply = 4;
                    tempTextureFactorDivide = 4;
                }
                else if (textureSizeY == 256) {
                    tempTextureFactorMultiply = 4;
                    tempTextureFactorDivide = 4;
                }
                else if (textureSizeY == 512) {
                    tempTextureFactorMultiply = 4;
                    tempTextureFactorDivide = 1;
                }

                //if floor or cieling
                if (tempPlane.vertex1.z == tempPlane.vertex3.z) {
                    //create vertex x4/y4/z4
                    tempPlane.vertex4.y = tempPlane.vertex3.y;
                    tempPlane.vertex4.x = tempPlane.vertex1.x;
                    tempPlane.vertex4.z = tempPlane.vertex2.z;

                    level.allHitboxes[level.currentHitbox].vertex[0] = tempPlane.vertex1;
                    level.allHitboxes[level.currentHitbox].vertex[1] = tempPlane.vertex2;
                    level.allHitboxes[level.currentHitbox].vertex[2] = tempPlane.vertex3;
                    level.allHitboxes[level.currentHitbox].vertex[3] = tempPlane.vertex4;
                    level.allHitboxes[level.currentHitbox].vertex[7] = tempPlane.vertex1;
                    level.allHitboxes[level.currentHitbox].vertex[6] = tempPlane.vertex2;
                    level.allHitboxes[level.currentHitbox].vertex[5] = tempPlane.vertex3;
                    level.allHitboxes[level.currentHitbox].vertex[4] = tempPlane.vertex4;
                    collisionsAlreadySet = true;
                    //create texture coordinates
                    if (textureMode == 0) {
                        tempPlane.y0 = tempPlane.vertex1.x * -uscale * 2 + uaxis / 2;
                        tempPlane.x0 = tempPlane.vertex3.y * -vscale * 2 + vaxis / 2;
                        tempPlane.y1 = tempPlane.vertex2.x * -uscale * 2 + uaxis / 2;
                        tempPlane.x1 = tempPlane.vertex1.y * -vscale * 2 + vaxis / 2;
                    }
                    if (textureMode == 1) {
                        tempPlane.y0 = tempPlane.vertex1.x * -uscale * 4 + uaxis / 2;
                        tempPlane.x0 = tempPlane.vertex3.y * -vscale * 4 + vaxis / 2;
                        tempPlane.y1 = tempPlane.vertex2.x * -uscale * 4 + uaxis / 2;
                        tempPlane.x1 = tempPlane.vertex1.y * -vscale * 4 + vaxis / 2;
                    }
                    //if cieling
                    if (tempPlane.vertex2.y == tempPlane.vertex3.y) {
                        //create vertex x4/y4/z4
                        tempPlane.vertex4.y = tempPlane.vertex1.y;
                        tempPlane.vertex4.x = tempPlane.vertex3.x;
                        tempPlane.vertex4.z = tempPlane.vertex2.z;
                        //create texture coordinates
                        if (textureMode == 0) {
                            tempPlane.y0 = tempPlane.vertex1.y * -uscale * 2 + uaxis / 2;
                            tempPlane.x0 = tempPlane.vertex3.x * -vscale * 2 + vaxis / 2;
                            tempPlane.y1 = tempPlane.vertex2.y * -uscale * 2 + uaxis / 2;
                            tempPlane.x1 = tempPlane.vertex1.x * -vscale * 2 + vaxis / 2;
                        }
                        if (textureMode == 1) {
                            tempPlane.y0 = tempPlane.vertex1.y * -uscale * 4 + uaxis / 2;
                            tempPlane.x0 = tempPlane.vertex3.x * -vscale * 4 + vaxis / 2;
                            tempPlane.y1 = tempPlane.vertex2.y * -uscale * 4 + uaxis / 2;
                            tempPlane.x1 = tempPlane.vertex1.x * -vscale * 4 + vaxis / 2;
                        }
                    }
                }
                //if wall is on the y axis
                else if (tempPlane.vertex1.x == tempPlane.vertex2.x) {
                    //create vertex x4/y4/z4
                    tempPlane.vertex4.y = tempPlane.vertex1.y;
                    tempPlane.vertex4.x = tempPlane.vertex3.x;
                    tempPlane.vertex4.z = tempPlane.vertex3.z;
                    //tempPlane.nx = tempPlane.vertex2.x + 128;
                    //tempPlane.ny = tempPlane.vertex2.y;
                    //tempPlane.nz = (tempPlane.vertex2.z - tempPlane.vertex3.z) / 2;
                    //create texture coordinates
                    if (textureMode == 0) {
                        tempPlane.y0 = tempPlane.vertex1.y * -uscale * 2 + uaxis / 2;
                        tempPlane.x0 = tempPlane.vertex3.z * -vscale * 2 + vaxis / 2 + 32;
                        tempPlane.y1 = tempPlane.vertex2.y * -uscale * 2 + uaxis / 2;
                        tempPlane.x1 = tempPlane.vertex1.z * -vscale * 2 + vaxis / 2 + 32;
                    }
                    else if (textureMode == 1) {
                        tempPlane.y0 = tempPlane.vertex1.y * -uscale * 4 + uaxis / 2;
                        tempPlane.x0 = tempPlane.vertex3.z * -vscale * 4 + vaxis / 2;
                        tempPlane.y1 = tempPlane.vertex2.y * -uscale * 4 + uaxis / 2;
                        tempPlane.x1 = tempPlane.vertex1.z * -vscale * 4 + vaxis / 2;
                    }
                }
                //if wall is on the x axis
                else if (tempPlane.vertex2.y == tempPlane.vertex3.y) {
                    //create vertex x4/y4/z4
                    tempPlane.vertex4.y = tempPlane.vertex3.y;
                    tempPlane.vertex4.x = tempPlane.vertex1.x;
                    tempPlane.vertex4.z = tempPlane.vertex3.z;

                    //create texture coordinates
                    if (textureMode == 0) {
                        tempPlane.y0 = tempPlane.vertex1.x * -uscale * 2 + uaxis / 2 + 32;
                        tempPlane.x0 = tempPlane.vertex3.z * -vscale * 2 + vaxis / 2 + 32;
                        tempPlane.y1 = tempPlane.vertex2.x * -uscale * 2 + uaxis / 2 + 32;
                        tempPlane.x1 = tempPlane.vertex1.z * -vscale * 2 + vaxis / 2 + 32;
                    }
                    else if (textureMode == 1) {
                        tempPlane.y0 = tempPlane.vertex1.x * -uscale * 4 + uaxis / 2;
                        tempPlane.x0 = tempPlane.vertex3.z * -vscale * 4 + vaxis / 2;
                        tempPlane.y1 = tempPlane.vertex2.x * -uscale * 4 + uaxis / 2;
                        tempPlane.x1 = tempPlane.vertex1.z * -vscale * 4 + vaxis / 2;
                    }
                }

                level.Plane[i] = tempPlane;
                level.allHitboxes[level.currentHitbox].isPlane = true;
                level.allHitboxes[level.currentHitbox].isDynamic = false;
                if (!collisionsAlreadySet) {
                    level.allHitboxes[level.currentHitbox].vertex[0] = tempPlane.vertex1;
                    level.allHitboxes[level.currentHitbox].vertex[1] = tempPlane.vertex2;
                    level.allHitboxes[level.currentHitbox].vertex[6] = tempPlane.vertex3;
                    level.allHitboxes[level.currentHitbox].vertex[7] = tempPlane.vertex4;
                    level.allHitboxes[level.currentHitbox].vertex[3] = tempPlane.vertex1;
                    level.allHitboxes[level.currentHitbox].vertex[2] = tempPlane.vertex2;
                    level.allHitboxes[level.currentHitbox].vertex[5] = tempPlane.vertex3;
                    level.allHitboxes[level.currentHitbox].vertex[4] = tempPlane.vertex4;
                }
                level.allHitboxes[level.currentHitbox].attachedPlane = &level.Plane[i];
                level.currentHitbox++;
                //printf("\nplane id:%d\nmaterial:%s\nx1:%s y1:%.0f z1:%.0f\nx2:%.0f y2:%.0f z2:%.0f\nx3:%.0f y3:%.0f z3:%.0f\n", planeId, tempMaterial, tempx1, level.Plane[i].vertex1.y, level.Plane[i].vertex1.z, level.Plane[i].vertex2.x, level.Plane[i].vertex2.y, level.Plane[i].vertex2.z, level.Plane[i].vertex3.x, level.Plane[i].vertex3.y, level.Plane[i].vertex3.z);
                //printf("\nplane id:%d\nuaxis:%.0f uscale:%.2f\nvaxis:%.0f vscale:%.2f\n", planeId, level.Plane[i].uaxis, level.Plane[i].uscale, level.Plane[i].vaxis, level.Plane[i].vscale);
                
                i++;
                //break;
            }
        }
        else if (strcmp(word, "\"info_player_start\"") == 0) // Read Player spawn
        {
            char tmpx[8];
            char tmpy[8];
            char tmpz[8];
            fscanf(levelFile, "%*31c%s %s %s", tmpx, tmpy, tmpz);
            //set the player positon
            localPlayer.position.x = (float)atof(tmpx) * LEVEL_SIZE;
            localPlayer.position.y = (float)atof(tmpy) * LEVEL_SIZE;
            localPlayer.position.z = (float)atof(tmpz) * LEVEL_SIZE;
        }
    }
    if (i >= MAX_PLANES)
        printf("Warning max Planes reached:%d", i);

    fclose(levelFile);
    
    level.planeCount = i;
    level.name = levelName;

    return 0;
}

void LoadMisc (void)
{
    w_portalgun_model = NE_ModelCreate(NE_Animated);
    w_portalgun_fire1_animation = NE_AnimationCreate();
    NE_AnimationLoad(w_portalgun_fire1_animation, w_portalgun_fire1_dsa_bin);
    NE_ModelLoadDSM(w_portalgun_model, w_portalgun_dsm_bin);
    NE_ModelSetAnimation(w_portalgun_model, w_portalgun_fire1_animation);
    NE_ModelSetMaterial(w_portalgun_model, w_portalgun_tex);
    NE_ModelScaleI(w_portalgun_model, floatToFixed(3, LEVEL_RENDER_SIZE), floatToFixed(3, LEVEL_RENDER_SIZE), floatToFixed(3, LEVEL_RENDER_SIZE));
    NE_ModelSetCoord(w_portalgun_model, 0, 0.1, 0);

    portal_orange_model = NE_ModelCreate(NE_Static);
    NE_ModelLoadStaticMesh(portal_orange_model, (u32 *)portal_bin);
    NE_ModelSetMaterial(portal_orange_model, portal_orange_tex);
    NE_ModelScaleI(portal_orange_model, floatToFixed(55,LEVEL_RENDER_SIZE), floatToFixed(55, LEVEL_RENDER_SIZE), floatToFixed(55, LEVEL_RENDER_SIZE));
    NE_ModelSetCoord(portal_orange_model, 0, -1, 0);

    portal_blue_model = NE_ModelCreate(NE_Static);
    NE_ModelLoadStaticMesh(portal_blue_model, (u32 *)portal_bin);
    NE_ModelSetMaterial(portal_blue_model, portal_blue_tex);
    NE_ModelScaleI(portal_blue_model, floatToFixed(55, LEVEL_RENDER_SIZE), floatToFixed(55, LEVEL_RENDER_SIZE), floatToFixed(55, LEVEL_RENDER_SIZE));
    NE_ModelSetCoord(portal_blue_model, 0, -1, 0);

    if (debugVision) {
        debug_vision_model = NE_ModelCreate(NE_Static);
        NE_ModelLoadStaticMesh(debug_vision_model, (u32 *)Debug_sphere_bin);
        NE_ModelSetMaterial(debug_vision_model, debugempty);
        NE_ModelScaleI(debug_vision_model, floatToFixed(10, LEVEL_RENDER_SIZE), floatToFixed(10, LEVEL_RENDER_SIZE), floatToFixed(10, LEVEL_RENDER_SIZE));
    }
}