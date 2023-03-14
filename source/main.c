// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2008-2011, 2019, 2022
//
// This file is part of Nitro Engine

#include <NEMain.h>
#include <fat.h>
#include <dirent.h>
#include <stdio.h>
#include <time.h>
#include "main.h"
#include "load.h"
#include "save.h"


int textureMode = 0;

NE_Camera* Camara;
NE_Model* Model[7];
NE_Physics* Physics[7];
Level level;

void Draw3DScene(void)
{
    NE_CameraUse(Camara);

     //The first 3 boxes will be affected by one light and 3 last boxes by
     //another one
    //NE_PolyFormat(31, 0, NE_LIGHT_0,NE_CULL_BACK, 0);
    //for (int i = 0; i < 3; i++)
    //    NE_ModelDraw(Model[i]);

    
    //CreateBlockSideManual(-256, -320, 64, 128, -320, 64, 128, -320, 320, 0.25, 0.25, white_wall_tile003a, 0, 11); //wall
    //CreateBlockSideManual(320, -128, 64, 320, 256, 64, 320, 256, 320, 0.25, 0.25, white_wall_tile003a, 0, 50); //wall
    //CreateBlockSideManual(128, -320, 64, 320, -320, 64, 320, -320, 320, 0.25, 0.25, black_wall_metal_002c, 0, 74); //wall
    //CreateBlockSideManual(320, -320, 64, 320, -128, 64, 320, -128, 320, 0.25, 0.25, black_wall_metal_002a, 0, 86); //wall
    //CreateBlockSideManual(320, 256, 64, -256, 256, 64, -256, 256, 320, 0.25, 0.25, white_wall_tile003a, 0, 104); //wall
    //CreateBlockSideManual(-256, 256, 64, -256, -320, 64, -256, -320, 320, 0.25, 0.25, white_wall_tile003a, 0, 110); //wall
    //CreateBlockSideManual(128, -320, 64, 128, -128, 64, 320, -128, 64, 0.25, 0.25, black_floor_metal_001c, 0, 13); //floor
    //CreateBlockSideManual(-256, -320, 64, -256, -128, 64, 128, -128, 64, 0.25, 0.25, white_floor_tile002a, 0, 42); //floor
    //CreateBlockSideManual(-256, -128, 64, -256, 256, 64, 320, 256, 64, 0.25, 0.25, white_floor_tile002a, 0, 66); //floor
    //CreateBlockSideManual(320, -128, 320, 128, -128, 320, 128, -320, 320, 0.25, 0.25, black_wall_metal_002b, 0, 138); //ceiling
    //CreateBlockSideManual(128, 256, 320, -256, 256, 320, -256, -320, 320, 0.25, 0.25, white_ceiling_tile002a, 0, 144); //ceiling
    //CreateBlockSideManual(320, 256, 320, 128, 256, 320, 128, -128, 320, 0.25, 0.25, white_ceiling_tile002a, 0, 150); //ceiling
}

int main(void)
{
    irqEnable(IRQ_HBLANK);
    irqSet(IRQ_VBLANK, NE_VBLFunc);
    irqSet(IRQ_HBLANK, NE_HBLFunc);

    NE_Init3D();

    fatInitDefault();

    // libnds uses VRAM_C for the text console, reserve A and B only
    NE_TextureSystemReset(0, 0, NE_VRAM_AB);
    // Init console in non-3D screen
    consoleDemoInit();

    Camara = NE_CameraCreate();

    NE_CameraSet(Camara,
                 -4, 3, 1,
                  0, 2, 0,
                  0, 1, 0);

    LoadTextures(textureMode);
    level.name = "test_map";
    //if (Plane->isDrawn)
    //printf("\nplane id:%d\nx1:%.0f x2:%.0f x3:%.0f\ny1:%.0f y2:%.0f y3:%.0f\nz1:%.0f z2:%.0f z3:%.0f\n", Plane->id, Plane->vertex1.x, Plane->vertex1.y, Plane->vertex1.z, Plane->vertex2.x, Plane->vertex2.y, Plane->vertex2.z, Plane->vertex3.x, Plane->vertex3.y, Plane->vertex3.z);


    mkdir("/_nds", 0777);
    mkdir("/_nds/PortalDS", 0777);
    mkdir("/_nds/PortalDS/levels", 0777);

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

    save();
    loadLevel();

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
            printf("\x1b[1;24HFPS: %d", fpscount);
            fpscount = 0;
        }

        //Camera
        // Get keys information
        scanKeys();
        uint32 keys = keysHeld();


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

        if (keys & KEY_START)
            break;

        NE_Process(Draw3DScene);
        RenderPlanes(level);

        // Increase frame count
        fpscount++;
    }

    return 0;
}
