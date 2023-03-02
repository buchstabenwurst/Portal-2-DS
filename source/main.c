// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2008-2011, 2019, 2022
//
// This file is part of Nitro Engine

#include <NEMain.h>
#include <time.h>
#include "main.h"
#include "load.h"

int textureMode = 0;

NE_Camera* Camara;
NE_Model* Model[7];
NE_Physics* Physics[7];


void Draw3DScene(void)
{
    NE_CameraUse(Camara);

     //The first 3 boxes will be affected by one light and 3 last boxes by
     //another one
    //NE_PolyFormat(31, 0, NE_LIGHT_0,NE_CULL_BACK, 0);
    //for (int i = 0; i < 3; i++)
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
    CreateBlockSide(-256, -320, 64, -256, -128, 64, 128, -128, 64, 0.25, 0.25, white_floor_tile002a, 0, 42); //floor
    CreateBlockSide(-256, -128, 64, -256, 256, 64, 320, 256, 64, 0.25, 0.25, white_floor_tile002a, 0, 66); //floor
    CreateBlockSide(320, -128, 320, 128, -128, 320, 128, -320, 320, 0.25, 0.25, black_floor_metal_001c, 0, 138); //ceiling
    CreateBlockSide(128, 256, 320, -256, 256, 320, -256, -320, 320, 0.25, 0.25, white_ceiling_tile002a, 0, 144); //ceiling
    CreateBlockSide(320, 256, 320, 128, 256, 320, 128, -128, 320, 0.25, 0.25, white_ceiling_tile002a, 0, 150); //ceiling


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

    // libnds uses VRAM_C for the text console, reserve A and B only
    NE_TextureSystemReset(0, 0, NE_VRAM_AB);
    // Init console in non-3D screen
    consoleDemoInit();

    Camara = NE_CameraCreate();

    NE_CameraSet(Camara,
                 -4, 3, 1,
                  0, 2, 0,
                  0, 1, 0);

    LoadTextures(0);

    // Create objects
    for (int i = 0; i < 3; i++)
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
    NE_PhysicsEnable(Physics[2], false);

    // Object coordinates
    NE_ModelSetCoord(Model[0], 0, 4,  1.5);
    NE_ModelSetCoord(Model[1], 0, 4,  0);
    NE_ModelSetCoord(Model[2], 0, 1, -1.5);

    // Set gravity
    NE_PhysicsSetGravity(Physics[0], 0.001);
    NE_PhysicsSetGravity(Physics[1], 0.001);
    NE_PhysicsSetGravity(Physics[2], 0.001);


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
    NE_ClearColorSet(NE_White, 31, 63);


    int angle = 0;

    int fpscount = 0;

    // This is used to see if second has changed
    int oldsec = 0;
    int seconds = 0;



    while (1)
    {
        NE_WaitForVBL(NE_UPDATE_PHYSICS);

        //FPS counter
        // Get time
        time_t unixTime = time(NULL);
        struct tm* timeStruct = gmtime((const time_t*)&unixTime);
        seconds = timeStruct->tm_sec;

        // If new second
        if (seconds != oldsec)
        {
            // Reset fps count and print current
            oldsec = seconds;
            printf("\x1b[6;1HFPS: %d", fpscount);
            fpscount = 0;
        }

        //Camera
        // Get keys information
        scanKeys();
        uint32 keys = keysHeld();


        printf("\x1b[1;1HPad: Rotate.\n\x1b[2;1HA/B: Move forward/back.");

        if (keys & KEY_DOWN)
            NE_CameraMoveFree(Camara, -0.05, 0, 0);
        else if (keys & KEY_UP)
            NE_CameraMoveFree(Camara, 0.05, 0, 0);

        if (keys & KEY_LEFT)
            NE_CameraMoveFree(Camara, 0, -0.05, 0);
        else if (keys & KEY_RIGHT)
            NE_CameraMoveFree(Camara, 0, 0.05, 0);

        if (keys & KEY_A)
            NE_CameraRotateFree(Camara, 0, 3, 0);
        else if (keys & KEY_Y)
            NE_CameraRotateFree(Camara, 0, -3, 0);

        if (keys & KEY_B && angle < 92)
        {
            angle += 3;
            NE_CameraRotateFree(Camara, 3, 0, 0);
        }
        else if (keys & KEY_X && angle > -92)
        {
            angle -= 3;
            NE_CameraRotateFree(Camara, -3, 0, 0);
        }

        NE_Process(Draw3DScene);

        // Increase frame count
        fpscount++;
    }

    return 0;
}
