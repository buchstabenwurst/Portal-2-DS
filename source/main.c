// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2008-2011, 2019, 2022
//
// This file is part of Nitro Engine

#include <NEMain.h>
#include <NECamera.h>
#include <nds/arm9/trig_lut.h>
#include <fat.h>
#include <filesystem.h>
#include <dirent.h>
#include <stdio.h>
#include <time.h>
#include "main.h"
#include "draw3d.h"
#include "load.h"
#include "save.h"
#include "physics.h"


int textureMode = 0;    //unused
int sensitivityHorizontal = 80;
int sensitivityVertical = 120;

bool debugText = true;
bool debugVision = false;

NE_Model* Model[7];
NE_Physics* Physics[7];
Level level;
PLAYER localPlayer;


int main(void)
{
    irqEnable(IRQ_HBLANK);
    irqSet(IRQ_VBLANK, NE_VBLFunc);
    irqSet(IRQ_HBLANK, NE_HBLFunc);

    NE_Init3D();
    NE_InitConsole();

    fatInitDefault();
    nitroFSInit(NULL);

    // libnds uses VRAM_C for the text console, reserve A and B only
    NE_TextureSystemReset(0, 0, NE_VRAM_AB);
    // Init console in non-3D screen
    consoleDemoInit();

    int fovValue = 80;
    Camara = NE_CameraCreate();
    NE_SetFov(fovValue);

    localPlayer.rotation.x = 0.1;
    localPlayer.rotation.y = 0;
    localPlayer.rotation.z = 0;
    localPlayer.position.x = 0;
    localPlayer.position.y = 0;
    localPlayer.position.z = 0.5;
    //NE_CameraSet(Camara,
    //             -0.4, 0.1, 0,
    //              0, 0.3, 0,
    //              0, 1, 0);

    NE_ClippingPlanesSet(0.01, 10);

    LoadTextures(textureMode);
    level.name = "test_map";
    //if (Plane->isDrawn)
    //printf("\nplane id:%d\nx1:%.0f x2:%.0f x3:%.0f\ny1:%.0f y2:%.0f y3:%.0f\nz1:%.0f z2:%.0f z3:%.0f\n", Plane->id, Plane->vertex1.x, Plane->vertex1.y, Plane->vertex1.z, Plane->vertex2.x, Plane->vertex2.y, Plane->vertex2.z, Plane->vertex3.x, Plane->vertex3.y, Plane->vertex3.z);


    mkdir("/_nds", 0777);
    mkdir("/_nds/PortalDS", 0777);
    mkdir("/_nds/PortalDS/levels", 0777);


    // Lights
    NE_LightSet(0, NE_White, -1, -1, 0);
    NE_LightSet(1, NE_Blue, -1, -1, 0);

    // Background
    NE_ClearColorSet(NE_White, 31, 63);


    int fpscount = 0;
    // This is used to see if second has changed
    int oldsec = 0;
    int seconds = 0;

    save();
    loadLevel();
    LoadMisc();

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


        if (keys & KEY_DOWN){
            localPlayer.physics.velocity.x += fixedToFloat(sinLerp(localPlayer.rotation.y * 32790) / 10, 20);
            localPlayer.physics.velocity.y += fixedToFloat(cosLerp(localPlayer.rotation.y * 32790) / 10, 20);
        }
        else if (keys & KEY_UP) {
            localPlayer.physics.velocity.x -= fixedToFloat(sinLerp(localPlayer.rotation.y * 32790) / 10, 20);
            localPlayer.physics.velocity.y -= fixedToFloat(cosLerp(localPlayer.rotation.y * 32790) / 10, 20);
        }

        if (keys & KEY_LEFT){
            localPlayer.physics.velocity.x -= fixedToFloat(cosLerp(localPlayer.rotation.y * 32790) / 10, 20);
            localPlayer.physics.velocity.y += fixedToFloat(sinLerp(localPlayer.rotation.y * 32790) / 10, 20);
        }
        else if (keys & KEY_RIGHT){
            localPlayer.physics.velocity.x += fixedToFloat(cosLerp(localPlayer.rotation.y * 32790) / 10, 20);
            localPlayer.physics.velocity.y -= fixedToFloat(sinLerp(localPlayer.rotation.y * 32790) / 10, 20);
        }
        
        
        
        if (keys & KEY_A) {
            localPlayer.rotation.y -= 0.000001 * sensitivityHorizontal * fovValue;
        }
        else if (keys & KEY_Y) {
            localPlayer.rotation.y += 0.000001 * sensitivityHorizontal * fovValue;
        }

        if (keys & KEY_B && localPlayer.rotation.z > -0.95)
        {
            localPlayer.rotation.z -= 0.000001 * sensitivityVertical * fovValue;
        }
        else if (keys & KEY_X && localPlayer.rotation.z < 0.95)
        {
            localPlayer.rotation.z += 0.000001 * sensitivityVertical * fovValue;
        }

        if (keys_down & KEY_TOUCH) 
        {
            if (localPlayer.physics.isGrounded){
                localPlayer.isJumping = true;
                localPlayer.physics.velocity.z = PLAYER_JUMPFORCE;
            }
        }

        if (keys & KEY_R) 
        {

        }


        if (keys & KEY_SELECT)
        {
            if (keys_down & KEY_R && fovValue > 20)
            {
                fovValue -= 20;
                NE_SetFov(fovValue);
            }

            if (keys_down & KEY_L && fovValue < 80)
            {
                fovValue += 20;
                NE_SetFov(fovValue);
            }

        }
        //NE_CameraSet(Camara, localPlayer.position.x, localPlayer.position.z, localPlayer.position.y, localPlayer.rotation.x, localPlayer.rotation.y, localPlayer.rotation.z + 1, localPlayer.position.x, localPlayer.position.y, localPlayer.position.z);
        //NE_AssertPointer(Camara, "NULL pointer");

        //Camara->matrix_is_updated = false;
        //Camara->from[0] = localPlayer.position.x;
        //Camara->from[1] = localPlayer.position.z;
        //Camara->from[2] = localPlayer.position.y;

        //Camara->to[0] += localPlayer.rotation.x;
        //Camara->to[1] += localPlayer.rotation.y;
        //Camara->to[2] += localPlayer.rotation.z;
        //NE_CameraMove(Camara, localPlayer.position.x, localPlayer.position.z, localPlayer.position.y);
        
        if (keys & KEY_START)
            break;

        //NE_ClearColorSet(NE_White, 31, 63);
        doPhysics();
        NE_Process(Draw3DScene);

        // Increase frame count
        fpscount++;
    }

    return 0;
}
