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
int sensitivityVertical = 140;

bool debugText = true;
bool debugVision = false;

Level level;
PLAYER localPlayer;
hitbox testBox, testBox2;


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

    localPlayer.rotation.x = 0;
    localPlayer.rotation.y = 0;
    localPlayer.rotation.z = 0;
    localPlayer.position.x = 0;
    localPlayer.position.y = 0;
    localPlayer.position.z = 0;


    NE_ClippingPlanesSet(0.001, 10);

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

    float rotation = 0;
    while (1)
    {
        NE_WaitForVBL(NE_UPDATE_ANIMATIONS);
        consoleClear();

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


    rotation += 1;

    float tmpsinZ = fixedToFloat(sinLerp(floatToFixed((rotation) /45, 12)), 12);
    float tmpcosZ = fixedToFloat(cosLerp(floatToFixed((rotation) /45, 12)), 12);
    //printf("\x1b[9;2H%f", tmpsinZ);
    //printf("\x1b[10;2H%f", rotation.z);

    Vector3 position;
    position.x = 0.1;
    position.y = 0.1;
    position.z = 120;

    
    testBox.vertex[0].x = position.x + 10 * tmpsinZ;
    testBox.vertex[0].y = position.y + 10 * tmpcosZ;
    testBox.vertex[0].z = position.z + 10;
    testBox.vertex[1].x = position.x + 10 * tmpcosZ;
    testBox.vertex[1].y = position.y + -10 * tmpsinZ;
    testBox.vertex[1].z = position.z + 10;
    testBox.vertex[2].x = position.x + -10 * tmpsinZ;
    testBox.vertex[2].y = position.y + -10 * tmpcosZ;
    testBox.vertex[2].z = position.z + 10;
    testBox.vertex[3].x = position.x + -10 * tmpcosZ;
    testBox.vertex[3].y = position.y + 10 * tmpsinZ;
    testBox.vertex[3].z = position.z + 10;

    testBox.vertex[4].x = position.x + -10 * tmpcosZ;
    testBox.vertex[4].y = position.y + 10 * tmpsinZ;
    testBox.vertex[4].z = position.z + -10;
    testBox.vertex[5].x = position.x + -10 * tmpsinZ;
    testBox.vertex[5].y = position.y + -10 * tmpcosZ;
    testBox.vertex[5].z = position.z + -10;
    testBox.vertex[6].x = position.x + 10 * tmpcosZ;
    testBox.vertex[6].y = position.y + -10 * tmpsinZ;
    testBox.vertex[6].z = position.z + -10;
    testBox.vertex[7].x = position.x + 10 * tmpsinZ;
    testBox.vertex[7].y = position.y + 10 * tmpcosZ;
    testBox.vertex[7].z = position.z + -10;

    float rotation2 = localPlayer.rotation.y *360;

    float tmpsin2Z = fixedToFloat(sinLerp(floatToFixed((rotation2) / 45, 12)), 12);
    float tmpcos2Z = fixedToFloat(cosLerp(floatToFixed((rotation2) / 45, 12)), 12);

    Vector3 position2;
    position2.x = localPlayer.position.x;
    position2.y = localPlayer.position.y;
    position2.z = localPlayer.position.z - 0.027;

    testBox2.vertex[0].x = position2.x + 10 * tmpsin2Z;
    testBox2.vertex[0].y = position2.y + 10 * tmpcos2Z;
    testBox2.vertex[0].z = position2.z + 10;
    testBox2.vertex[1].x = position2.x + 10 * tmpcos2Z;
    testBox2.vertex[1].y = position2.y + -10 * tmpsin2Z;
    testBox2.vertex[1].z = position2.z + 10;
    testBox2.vertex[2].x = position2.x + -10 * tmpsin2Z;
    testBox2.vertex[2].y = position2.y + -10 * tmpcos2Z;
    testBox2.vertex[2].z = position2.z + 10;
    testBox2.vertex[3].x = position2.x + -10 * tmpcos2Z;
    testBox2.vertex[3].y = position2.y + 10 * tmpsin2Z;
    testBox2.vertex[3].z = position2.z + 10;

    testBox2.vertex[4].x = position2.x + -10 * tmpcos2Z;
    testBox2.vertex[4].y = position2.y + 10 * tmpsin2Z;
    testBox2.vertex[4].z = position2.z + -10;
    testBox2.vertex[5].x = position2.x + -10 * tmpsin2Z;
    testBox2.vertex[5].y = position2.y + -10 * tmpcos2Z;
    testBox2.vertex[5].z = position2.z + -10;
    testBox2.vertex[6].x = position2.x + 10 * tmpcos2Z;
    testBox2.vertex[6].y = position2.y + -10 * tmpsin2Z;
    testBox2.vertex[6].z = position2.z + -10;
    testBox2.vertex[7].x = position2.x + 10 * tmpsin2Z;
    testBox2.vertex[7].y = position2.y + 10 * tmpcos2Z;
    testBox2.vertex[7].z = position2.z + -10;

    level.currentHitbox = 2;
    level.allHitboxes[0] = testBox;
    level.allHitboxes[0].isDynamic = true;
    level.allHitboxes[1] = testBox2;
    level.allHitboxes[1].isDynamic = true;

        //Camera
        // Get keys information
        scanKeys();
        uint32 keys = keysHeld();
        uint32 keys_down = keysDown();


        if (keys & KEY_DOWN){
            localPlayer.physics.velocity.x += fixedToFloat(sinLerp(localPlayer.rotation.y * 32790) * (LEVEL_SIZE * 100), 20);
            localPlayer.physics.velocity.y += fixedToFloat(cosLerp(localPlayer.rotation.y * 32790) * (LEVEL_SIZE * 100), 20);
        }
        else if (keys & KEY_UP) {
            localPlayer.physics.velocity.x -= fixedToFloat(sinLerp(localPlayer.rotation.y * 32790) * (LEVEL_SIZE * 100), 20);
            localPlayer.physics.velocity.y -= fixedToFloat(cosLerp(localPlayer.rotation.y * 32790) * (LEVEL_SIZE * 100), 20);
        }

        if (keys & KEY_LEFT){
            localPlayer.physics.velocity.x -= fixedToFloat(cosLerp(localPlayer.rotation.y * 32790) * (LEVEL_SIZE * 100), 20);
            localPlayer.physics.velocity.y += fixedToFloat(sinLerp(localPlayer.rotation.y * 32790) * (LEVEL_SIZE * 100), 20);
        }
        else if (keys & KEY_RIGHT){
            localPlayer.physics.velocity.x += fixedToFloat(cosLerp(localPlayer.rotation.y * 32790) * (LEVEL_SIZE * 100), 20);
            localPlayer.physics.velocity.y -= fixedToFloat(sinLerp(localPlayer.rotation.y * 32790) * (LEVEL_SIZE * 100), 20);
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

        if (keys_down & KEY_R && !(keys & KEY_SELECT)) 
        {
            NE_ModelAnimStart(w_portalgun_model, NE_ANIM_ONESHOT, floattof32(1));
            shootPortal(0);
        }

        if (keys_down & KEY_L && !(keys & KEY_SELECT)) 
        {
            NE_ModelAnimStart(w_portalgun_model, NE_ANIM_ONESHOT, floattof32(1));
            shootPortal(1);
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
