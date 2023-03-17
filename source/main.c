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
#include "draw3d.h"
#include "load.h"
#include "save.h"


int textureMode = 0;

NE_Model* Model[7];
NE_Physics* Physics[7];
Level level;


int main(void)
{
    irqEnable(IRQ_HBLANK);
    irqSet(IRQ_VBLANK, NE_VBLFunc);
    irqSet(IRQ_HBLANK, NE_HBLFunc);

    NE_Init3D();
    NE_InitConsole();

    fatInitDefault();

    // libnds uses VRAM_C for the text console, reserve A and B only
    NE_TextureSystemReset(0, 0, NE_VRAM_AB);
    // Init console in non-3D screen
    consoleDemoInit();

    int fovValue = 80;
    Camara = NE_CameraCreate();

    NE_CameraSet(Camara,
                 -0.4, 0.3, 0,
                  0, 0.3, 0,
                  0, 1, 0);

    NE_ClippingPlanesSet(0.01, 10);
    NE_SetFov(fovValue);

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
    int freemem = NE_TextureFreeMemPercent();

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
            printf("\x1b[1;20HFPS: %d", fpscount);
            fpscount = 0;
        }


        printf("\x1b[2;20HVram left:%d", freemem);

        //Camera
        // Get keys information
        scanKeys();
        uint32 keys = keysHeld();
        uint32 keys_down = keysDown();


        if (keys & KEY_DOWN)
            NE_CameraMoveFree(Camara, -0.005, 0, 0);
        else if (keys & KEY_UP)
            NE_CameraMoveFree(Camara, 0.005, 0, 0);

        if (keys & KEY_LEFT)
            NE_CameraMoveFree(Camara, 0, -0.005, 0);
        else if (keys & KEY_RIGHT)
            NE_CameraMoveFree(Camara, 0, 0.005, 0);

        if (keys & KEY_A) {
            NE_CameraRotateFree(Camara, 0, fovValue / 26, 0);
        }
        else if (keys & KEY_Y) {
            NE_CameraRotateFree(Camara, 0, fovValue / -26, 0);
        }

        if (keys & KEY_B && angle < 96)
        {
            angle += fovValue / 26;
            NE_CameraRotateFree(Camara, fovValue / 26, 0, 0);
        }
        else if (keys & KEY_X && angle > -96)
        {
            angle -= fovValue / 26;
            NE_CameraRotateFree(Camara, fovValue / -26, 0, 0);
        }

        if (keys & KEY_R) 
        {

        }


        if (keys & KEY_SELECT)
        {
            if (keys_down & KEY_R && fovValue > 30)
            {
                fovValue -= 10;
            }

            if (keys_down & KEY_L && fovValue < 80)
            {
                fovValue += 10;
            }

            if (angle <= -96) 
            {
                angle += 16;
                NE_CameraRotateFree(Camara, 16, 0, 0);
            }
            if (angle >= 96) 
            {
                angle -= 16;
                NE_CameraRotateFree(Camara, -16, 0, 0);
            }

            NE_SetFov(fovValue);
        }

        
        
        if (keys & KEY_START)
            break;

        //NE_ClearColorSet(NE_White, 31, 63);
        NE_Process(Draw3DScene);

        // Increase frame count
        fpscount++;
    }

    return 0;
}
