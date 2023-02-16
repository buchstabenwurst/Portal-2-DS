// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2008-2011, 2019, 2022
//
// This file is part of Nitro Engine

#include <NEMain.h>
#include "load.h"
#include "main.h"

#include "cube_bin.h"
#include "debug_plane_bin.h"
#include "white_wall_tile003a_tex_bin.h"
#include "black_floor_metal_001c_tex_bin.h"
#include "Debug_tex_bin.h"
#include "debugempty_tex_bin.h"

NE_Camera* Camara;
Block* block = NULL;
NE_Model* Model[7];
NE_Material* white_wall_tile003a;
NE_Material* black_floor_metal_001c;
NE_Material* Debug_Material;
NE_Material* debugempty;
NE_Physics* Physics[7];


void Draw3DScene(void)
{
    NE_CameraUse(Camara);

    // The first 3 boxes will be affected by one light and 3 last boxes by
    // another one
    //NE_PolyFormat(31, 0, NE_LIGHT_0,NE_CULL_BACK, 0);
    //for (int i = 0; i < 3; i++)
    //    NE_ModelDraw(Model[i]);

    //NE_PolyFormat(31, 0, NE_LIGHT_1,NE_CULL_BACK, 0);
    //for (int i = 3; i < 6; i++)
    //    NE_ModelDraw(Model[i]);

    //Draw Map (just Blocks for now)
    //NE_PolyFormat(31, 1, NE_LIGHT_0, NE_CULL_NONE, 0);
    //NE_ModelDraw(block->Model);


    CreateBlockSide(-256, -320, 64, 128, -320, 64, 128, -320, 320, 0.25, 0.25, white_wall_tile003a, 0, 11); //wall
    CreateBlockSide(320, -128, 64, 320, 256, 64, 320, 256, 320, 0.25, 0.25, white_wall_tile003a, 0, 50); //wall
    CreateBlockSide(128, -320, 64, 320, -320, 64, 320, -320, 320, 0.25, 0.25, black_floor_metal_001c, 0, 74); //wall
    CreateBlockSide(320, -320, 64, 320, -128, 64, 320, -128, 320, 0.25, 0.25, black_floor_metal_001c, 0, 86); //wall
    CreateBlockSide(320, 256, 64, -256, 256, 64, -256, 256, 320, 0.25, 0.25, white_wall_tile003a, 0, 104); //wall
    CreateBlockSide(-256, 256, 64, -256, -320, 64, -256, -320, 320, 0.25, 0.25, white_wall_tile003a, 0, 110); //wall
    CreateBlockSide(128, -320, 64, 128, -128, 64, 320, -128, 64, 0.25, 0.25, black_floor_metal_001c, 0, 13); //floor
    CreateBlockSide(-256, -320, 64, -256, -128, 64, 128, -128, 64, 0.25, 0.25, white_wall_tile003a, 0, 42); //floor
    CreateBlockSide(-256, -128, 64, -256, 256, 64, 320, 256, 64, 0.25, 0.25, white_wall_tile003a, 0, 66); //floor
    CreateBlockSide(320, -128, 320, 128, -128, 320, 128, -320, 320, 0.25, 0.25, black_floor_metal_001c, 0, 138); //ceiling
    CreateBlockSide(128, 256, 320, -256, 256, 320, -256, -320, 320, 0.25, 0.25, white_wall_tile003a, 0, 144); //ceiling
    CreateBlockSide(320, 256, 320, 128, 256, 320, 128, -128, 320, 0.25, 0.25, white_wall_tile003a, 0, 150); //ceiling


    //NE_MaterialUse(debugempty);
    ////NE_MaterialUse(white_wall_tile003a);
    //NE_PolyBegin(GL_QUAD);

    //NE_PolyColor(NE_Red);    // Set next vertices color
    //NE_PolyTexCoord(0, 0);   // Texture coordinates
    //NE_PolyVertex(-1, 1, 0); // Send new vertex

    //NE_PolyColor(NE_Blue);
    //NE_PolyTexCoord(0, 64);
    //NE_PolyVertex(-1, -1, 0);

    //NE_PolyColor(NE_Green);
    //NE_PolyTexCoord(64, 64);
    //NE_PolyVertex(1, -1, 0);

    //NE_PolyColor(NE_Yellow);
    //NE_PolyTexCoord(64, 0);
    //NE_PolyVertex(1, 1, 0);

    //// Apparently this command is ignored by the GPU
    //NE_PolyEnd();

}

int main(void)
{
    irqEnable(IRQ_HBLANK);
    irqSet(IRQ_VBLANK, NE_VBLFunc);
    irqSet(IRQ_HBLANK, NE_HBLFunc);

    NE_Init3D();

    Camara = NE_CameraCreate();
    white_wall_tile003a = NE_MaterialCreate();
    black_floor_metal_001c = NE_MaterialCreate();
    Debug_Material = NE_MaterialCreate();
    debugempty = NE_MaterialCreate();

    NE_CameraSet(Camara,
                 -4, 3, 1,
                  0, 2, 0,
                  0, 1, 0);

    // Create objects
    for (int i = 0; i < 6; i++)
    {
        Model[i] = NE_ModelCreate(NE_Static);
        Physics[i] = NE_PhysicsCreate(NE_BoundingBox);


        NE_ModelLoadStaticMesh(Model[i], (u32 *)cube_bin);

        NE_PhysicsSetModel(Physics[i], // Physics object
                           (void *)Model[i]); // Model assigned to it

        NE_PhysicsEnable(Physics[i], false);
        NE_PhysicsSetSize(Physics[i], 1, 1, 1);
    }

    

    // Enable only the ones we will move
    NE_PhysicsEnable(Physics[0], true);
    NE_PhysicsEnable(Physics[1], true);
    NE_PhysicsEnable(Physics[2], true);
    NE_PhysicsEnable(Physics[3], false);
    NE_PhysicsEnable(Physics[4], false);
    NE_PhysicsEnable(Physics[5], false);

    // Object coordinates
    NE_ModelSetCoord(Model[0], 0, 4,  1.5);
    NE_ModelSetCoord(Model[1], 0, 4,  0);
    NE_ModelSetCoord(Model[2], 0, 4, -1.5);
    NE_ModelSetCoord(Model[3], 0, 0,  1.5);
    NE_ModelSetCoord(Model[4], 0, -5,  0);
    NE_ModelSetCoord(Model[5], 0, 0, -1.5);

    // Set gravity
    NE_PhysicsSetGravity(Physics[0], 0.001);
    NE_PhysicsSetGravity(Physics[1], 0.001);
    NE_PhysicsSetGravity(Physics[2], 0.001);
    NE_PhysicsSetGravity(Physics[3], 0.001);
    NE_PhysicsSetGravity(Physics[4], 0.001);
    NE_PhysicsSetGravity(Physics[5], 0.001);


    // Tell the engine what to do if there is a collision
    NE_PhysicsOnCollision(Physics[0], NE_ColBounce);
    NE_PhysicsOnCollision(Physics[1], NE_ColBounce);
    NE_PhysicsOnCollision(Physics[2], NE_ColBounce);

    // Set percent of energy kept after a bounce
    // Default is 50, 100 = no energy lost.
    NE_PhysicsSetBounceEnergy(Physics[0], 20);
    NE_PhysicsSetBounceEnergy(Physics[1], 20);
    NE_PhysicsSetBounceEnergy(Physics[2], 50);

    // Lights
    NE_LightSet(0, NE_White, -1, -1, 0);
    NE_LightSet(1, NE_Blue, -1, -1, 0);

    // Background
    NE_ClearColorSet(NE_Red, 31, 63);


    int angle = 0;


    NE_MaterialTexLoad(white_wall_tile003a, NE_A1RGB5, 256,256, NE_TEXGEN_TEXCOORD,
        (u8*)white_wall_tile003a_tex_bin);

    NE_MaterialTexLoad(black_floor_metal_001c, NE_A1RGB5, 256,256, NE_TEXGEN_TEXCOORD,
        (u8*)black_floor_metal_001c_tex_bin);

    NE_MaterialTexLoad(Debug_Material, NE_A1RGB5, 128, 128, NE_TEXGEN_TEXCOORD,
        (u8*)Debug_tex_bin);

    NE_MaterialTexLoad(debugempty, NE_A1RGB5, 64, 64, NE_TEXGEN_POSITION,
        (u8*)debugempty_tex_bin);

    while (1)
    {
        NE_WaitForVBL(NE_UPDATE_PHYSICS);

        // Get keys information
        scanKeys();
        uint32 keys = keysHeld();

        printf("\x1b[0;0HPad: Rotate.\nA/B: Move forward/back.");

        if (keys & KEY_DOWN && angle < 92)
        {
            angle += 3;
            NE_CameraRotateFree(Camara, 3, 0, 0);
        }
        else if (keys & KEY_UP && angle > -92)
        {
            angle -= 3;
            NE_CameraRotateFree(Camara, -3, 0, 0);
        }

        if (keys & KEY_LEFT)
            NE_CameraRotateFree(Camara, 0, -3, 0);
        else if (keys & KEY_RIGHT)
            NE_CameraRotateFree(Camara, 0, 3, 0);

        if (keys & KEY_A)
            NE_CameraMoveFree(Camara, 0.05, 0, 0);
        else if (keys & KEY_B)
            NE_CameraMoveFree(Camara, -0.05, 0, 0);

        NE_Process(Draw3DScene);
    }

    return 0;
}
