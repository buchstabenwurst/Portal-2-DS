// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2008-2011, 2019, 2022
//
// This file is part of Nitro Engine

#include <NEMain.h>
#include <NECamera.h>
#include <nds.h>
#include <nds/arm9/trig_lut.h>
#include <fat.h>
#include <filesystem.h>
#include <dirent.h>
#include <stdio.h>
#include <time.h>
#include <dswifi9.h>
#include <memory.h>
#include "main.h"
#include "draw3d.h"
#include "load.h"
#include "save.h"
#include "physics.h"
#include "wifi.h"

tNDSBanner banner;

int textureMode = 0;    //unused
int sensitivityHorizontal = 80;
int sensitivityVertical = 140;

bool debugText = true;
bool debugVision = false;

Level level;
PLAYER localPlayer;
hitbox testBox, testBox2;


void SendDownloadPlay() {
    tempSendBuffer[0] = 0xD3;
    tempSendBuffer[1] = 0x21;
    tempSendBuffer[2] = 0x0201;
    tempSendBuffer[3] = 0x8482;
    tempSendBuffer[4] = 0x0103;
    tempSendBuffer[5] = 0x0507;
    tempSendBuffer[6] = 0x05;
    tempSendBuffer[7] = 0x02;
    tempSendBuffer[8] = 0;
    tempSendBuffer[9] = 0x88DD;
    tempSendBuffer[10] = 0x0900;
    tempSendBuffer[11] = 0x00BF;
    tempSendBuffer[12] = 0x0A;
    tempSendBuffer[13] = 0;
    tempSendBuffer[14] = 0x01;
    tempSendBuffer[15] = 0;
    tempSendBuffer[16] = 0x25;
    tempSendBuffer[17] = 0;
    tempSendBuffer[18] = 0;
    tempSendBuffer[19] = 0x0B70;
    tempSendBuffer[20] = 0x01FE;
    tempSendBuffer[21] = 0x08;
    tempSendBuffer[22] = 0x25;
    tempSendBuffer[23] = 0;



    memset(tempSendBuffer + 24, 0x00, 137);

    tempSendBuffer[24] = 0;
    tempSendBuffer[25] = (unsigned short)beaconNum * 0x0100;
    tempSendBuffer[26] = 0xAAAA; // Checksum 
    tempSendBuffer[27] = 0x0900 + (unsigned short)beaconNum;
    tempSendBuffer[28] = 0x0062;

    userTheme = PersonalData->theme;
    usernameLength = PersonalData->nameLen;
    for (int j = 0; j < usernameLength; j++)
        username[j] = PersonalData->name[j];

    switch (beaconNum) {
    case 0:
        for (int j = 0, k = 0; k < 16; j += 2, k++) {
            tempSendBuffer[29 + k] = (pallette[j] + pallette[j + 1] * 0x0100) & 0xFFFF;  // convert two 0x00 to one 0x0000
        }
        for (int j = 0, k = 0; k < 116; j += 2, k++) {
            tempSendBuffer[45 + k] = (icon[j] + icon[j + 1] * 0x0100) & 0xFFFF;
        }break;

    case 1:
        for (int j = 66, k = 0; k < 132; j += 2, k++) {
            tempSendBuffer[29 + k] = (icon[j] + icon[j + 1] * 0x0100) & 0xFFFF;
        }break;

    case 2:
        for (int j = 164, k = 0; k < 132; j += 2, k++) {
            tempSendBuffer[29 + k] = (icon[j] + icon[j + 1] * 0x0100) & 0xFFFF;
        }break;

    case 3:
        for (int j = 262, k = 0; k < 132; j += 2, k++) {
            tempSendBuffer[29 + k] = (icon[j] + icon[j + 1] * 0x0100) & 0xFFFF;
        }break;

    case 4:
        for (int j = 360, k = 0; k < 132; j += 2, k++) {
            tempSendBuffer[29 + k] = (icon[j] + icon[j + 1] * 0x0100) & 0xFFFF;
        }break;

    case 5:
        for (int j = 458, k = 0; k < 27; j += 2, k++) {
            tempSendBuffer[29 + k] = (icon[j] + icon[j + 1] * 0x0100) & 0xFFFF;
        }

        tempSendBuffer[56] = (userTheme + usernameLength * 0x0100) & 0xFFFF;
        for (int j = 0; j < 10; j++) {
            tempSendBuffer[57 + j] = username[j];
        }

        tempSendBuffer[67] = maxPlayers;
        for (int j = 0; j < 10; j++) {
            tempSendBuffer[68 + j] = title[j];
        }break;

    case 6:
        for (int j = 10; j < 48; j++) {
            tempSendBuffer[19 + j] = title[j];
        }

        for (int j = 0; j < 96; j++) {
            tempSendBuffer[67 + j] = description[j];
        }break;

    case 7:
        for (int j = 11; j < 96; j++) {
            tempSendBuffer[18 + j] = description[j];
        }break;

    case 8:
        tempSendBuffer[28] = 0x0048;

        for (int j = 60; j < 96; j++) {
            tempSendBuffer[-31 + j] = description[j];
        }break;

    case 9:
        tempSendBuffer[27] = 0x0901;
        tempSendBuffer[28] = 0x0001;
        tempSendBuffer[24] = 0x02;
        break;
    }
    

    unsigned int checksum = 0;
    for (int j = 27; j <= 77; j++) {
        checksum += tempSendBuffer[j];
    }
    checksum = 0xFFFF & ~(checksum + checksum / 0x10000);
    tempSendBuffer[26] = checksum; // Checksum
    printf("\x1b[2;20H%x", tempSendBuffer[77]);
    printf("\x1b[3;20H%x", checksum);

    printf("\x1b[1;20H%d", beaconNum);

    Wifi_RawTxFrameMultiboot(156, 0x0014, tempSendBuffer);
    //Wifi_RawTxFrameMultiboot(19, 0x0014, (unsigned short*)title);
    swiIntrWait(0, IRQ_FIFO_EMPTY);
    beaconNum++;
    if (beaconNum > 9)
        beaconNum = 0;
}
int main(void)
{
    irqEnable(IRQ_HBLANK);
    irqEnable(IRQ_FIFO_EMPTY);
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




    printf("\nInit NiFi...\n");

    // Changes how packets are handled
    Wifi_SetRawPacketMode(PACKET_MODE_NIFI);

    // Init Wifi without automatic settings
    Wifi_InitDefault(false);

    // Enable Wifi
    Wifi_EnableWifi();

    // Force specific channel for communication
    Wifi_SetChannel(wifiChannel);

    loadIcon();
    initDownloadPlay();


    //calls the timerCallBack function 4 times per second.
    timerStart(0, ClockDivider_1024, TIMER_FREQ_1024(5), SendDownloadPlay);

    while (1) {
    
    };

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


        int rotation = 10;

        float tmpsinZ = fixedToFloat(sinLerp(floatToFixed((rotation) /45, 12)), 12);
        float tmpcosZ = fixedToFloat(cosLerp(floatToFixed((rotation) /45, 12)), 12);
        //printf("\x1b[9;2H%f", tmpsinZ);
        //printf("\x1b[10;2H%f", rotation.z);

        Vector3 position;
        position.x = 0.1;
        position.y = 0.1;
        position.z = 0.1;

    
        testBox.vertex[0].x = position.x + 0.01 * tmpsinZ;
        testBox.vertex[0].y = position.y + 0.01 * tmpcosZ;
        testBox.vertex[0].z = position.z + 0.01;
        testBox.vertex[1].x = position.x + 0.01 * tmpcosZ;
        testBox.vertex[1].y = position.y + -0.01 * tmpsinZ;
        testBox.vertex[1].z = position.z + 0.01;
        testBox.vertex[2].x = position.x + -0.01 * tmpsinZ;
        testBox.vertex[2].y = position.y + -0.01 * tmpcosZ;
        testBox.vertex[2].z = position.z + 0.01;
        testBox.vertex[3].x = position.x + -0.01 * tmpcosZ;
        testBox.vertex[3].y = position.y + 0.01 * tmpsinZ;
        testBox.vertex[3].z = position.z + 0.01;

        testBox.vertex[4].x = position.x + -0.01 * tmpcosZ;
        testBox.vertex[4].y = position.y + 0.01 * tmpsinZ;
        testBox.vertex[4].z = position.z + -0.01;
        testBox.vertex[5].x = position.x + -0.01 * tmpsinZ;
        testBox.vertex[5].y = position.y + -0.01 * tmpcosZ;
        testBox.vertex[5].z = position.z + -0.01;
        testBox.vertex[6].x = position.x + 0.01 * tmpcosZ;
        testBox.vertex[6].y = position.y + -0.01 * tmpsinZ;
        testBox.vertex[6].z = position.z + -0.01;
        testBox.vertex[7].x = position.x + 0.01 * tmpsinZ;
        testBox.vertex[7].y = position.y + 0.01 * tmpcosZ;
        testBox.vertex[7].z = position.z + -0.01;

        int rotation2 = 0;

        float tmpsin2Z = fixedToFloat(sinLerp(floatToFixed((rotation2) / 45, 12)), 12);
        float tmpcos2Z = fixedToFloat(cosLerp(floatToFixed((rotation2) / 45, 12)), 12);

        Vector3 position2;
        position2.x = localPlayer.position.x;
        position2.y = localPlayer.position.y;
        position2.z = localPlayer.position.z - 0.027;

        testBox2.vertex[0].x = position2.x + 0.01 * tmpsin2Z;
        testBox2.vertex[0].y = position2.y + 0.01 * tmpcos2Z;
        testBox2.vertex[0].z = position2.z + 0.01;
        testBox2.vertex[1].x = position2.x + 0.01 * tmpcos2Z;
        testBox2.vertex[1].y = position2.y + -0.01 * tmpsin2Z;
        testBox2.vertex[1].z = position2.z + 0.01;
        testBox2.vertex[2].x = position2.x + -0.01 * tmpsin2Z;
        testBox2.vertex[2].y = position2.y + -0.01 * tmpcos2Z;
        testBox2.vertex[2].z = position2.z + 0.01;
        testBox2.vertex[3].x = position2.x + -0.01 * tmpcos2Z;
        testBox2.vertex[3].y = position2.y + 0.01 * tmpsin2Z;
        testBox2.vertex[3].z = position2.z + 0.01;

        testBox2.vertex[4].x = position2.x + -0.01 * tmpcos2Z;
        testBox2.vertex[4].y = position2.y + 0.01 * tmpsin2Z;
        testBox2.vertex[4].z = position2.z + -0.01;
        testBox2.vertex[5].x = position2.x + -0.01 * tmpsin2Z;
        testBox2.vertex[5].y = position2.y + -0.01 * tmpcos2Z;
        testBox2.vertex[5].z = position2.z + -0.01;
        testBox2.vertex[6].x = position2.x + 0.01 * tmpcos2Z;
        testBox2.vertex[6].y = position2.y + -0.01 * tmpsin2Z;
        testBox2.vertex[6].z = position2.z + -0.01;
        testBox2.vertex[7].x = position2.x + 0.01 * tmpsin2Z;
        testBox2.vertex[7].y = position2.y + 0.01 * tmpcos2Z;
        testBox2.vertex[7].z = position2.z + -0.01;


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
