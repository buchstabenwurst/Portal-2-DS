#include <NEMain.h>
#include "main.h"
#include "load.h"

Block* block;
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
    black_floor_metal_001c = NE_MaterialCreate();
    black_wall_metal_002c = NE_MaterialCreate();

    //for when you can create multiple texture usig one pallete
    //tile_cleanPal16 = NE_PaletteCreate();
    //metal_cleanPal16 = NE_PaletteCreate();

    white_ceiling_tile002aPal = NE_PaletteCreate();
    white_floor_tile002aPal = NE_PaletteCreate();
    white_wall_tile003aPal = NE_PaletteCreate();
    black_floor_metal_001cPal = NE_PaletteCreate();
    black_wall_metal_002cPal = NE_PaletteCreate();

    if (textureMode == 0)
    {
        LoadPal16(white_ceiling_tile002a, (u8*)white_ceiling_tile002a_tex_bin, white_ceiling_tile002aPal, (void*)white_ceiling_tile002a_pal_bin, 256);

        LoadPal16(white_floor_tile002a, (u8*)white_floor_tile002a_tex_bin, white_floor_tile002aPal, (void*)white_floor_tile002a_pal_bin, 256);

        LoadPal16(white_wall_tile003a, (u8*)white_wall_tile003a_tex_bin, white_wall_tile003aPal, (void*)white_wall_tile003a_pal_bin, 128);

        LoadPal16(black_floor_metal_001c, (u8*)black_floor_metal_001c_tex_bin, black_floor_metal_001cPal, (void*)black_floor_metal_001c_pal_bin, 128);

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

    NE_MaterialTexLoad(Debug_Material, NE_A1RGB5, 128, 128, NE_TEXGEN_TEXCOORD,
        (u8*)Debug_tex_bin);

    NE_MaterialTexLoad(debugempty, NE_A1RGB5, 64, 64, NE_TEXGEN_POSITION,
        (u8*)debugempty_tex_bin);
}

//i split blocks to sides for using the nodraw texture
// @param x1,y1,z1 vertex 1 position
// @param x2,y2,z2 vertex 2 position
// @param x3,y3,z3 vertex 3 position
// @param id is id

void CreateBlockSide(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, double u, double v, NE_Material *Material, int Zone, int id) {
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

    else if(y1 == y2){  //look if side is y aligned wall and create vertex x4/y4/z4
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
    else if(x2 == x3){  //else side is x aligned wall, create vertex x4
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
    NE_PolyFormat(31, 1, NE_LIGHT_0 ,NE_CULL_BACK , 0);

    NE_MaterialUse(Material);

    NE_PolyBegin(GL_QUAD);
        //NE_PolyNormal(nx / 100, nz / 100, ny / 100);

        NE_PolyTexCoord(v0, u1);
        NE_PolyVertex(x1 / 100, z1 / 100, y1 / 100);

        NE_PolyTexCoord(v1, u1);
        NE_PolyVertex(x2 / 100, z2 / 100, y2 / 100);

        NE_PolyTexCoord(v1, u0);
        NE_PolyVertex(x3 / 100, z3 / 100, y3 / 100);

        NE_PolyTexCoord(v0, u0);
        NE_PolyVertex(x4 / 100, z4 / 100, y4 / 100);

    NE_PolyEnd();

    //block->Model = NE_ModelCreate(NE_Static);
    //block->Physics = NE_PhysicsCreate(NE_BoundingBox);
    //NE_ModelLoadStaticMesh(block->Model, (u32*)plane_bin);
    //NE_PhysicsSetSize(block->Physics, x1 + x2, -y1 + y2, z2 - z3);    //collision anwenden

    //NE_PhysicsSetModel(block->Physics, // Physics object
    //    (void*)block->Model); // Model assigned to it

    //NE_PhysicsEnable(block->Physics, false);
}