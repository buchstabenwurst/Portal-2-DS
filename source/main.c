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
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <squirrel.h>
#include <sqstdio.h>
#include <sqstdblob.h>
#include <sqstdsystem.h>
#include <sqstdmath.h>
#include <sqstdstring.h>
#include <sqstdaux.h>
#include "main.h"
#include "draw3d.h"
#include "load.h"
#include "save.h"
#include "physics.h"
#include "console.h"

int textureMode = 0;    //unused
int sensitivityHorizontal = 80;
int sensitivityVertical = 140;

bool isConsoleOpen = false;
bool debugText = false;
bool debugVision = false;

HSQUIRRELVM squirrelvm;
Level level;
PLAYER localPlayer;
Cube cubes[10];
int lastCube = 0;
Keyboard *keyboard;

void addCube(Vector3 position) {
    cubes[lastCube].position = position;

    Vector3 size;
    size.x = 20;
    size.y = 20;
    size.z = 30;

    addHitbox(size, &cubes[lastCube].position, &cubes[lastCube].rotation, 1);
    lastCube++;
}

#include <stdarg.h>
void printfunc(HSQUIRRELVM SQ_UNUSED_ARG(v),const SQChar *s,...)
{
    va_list vl;
    va_start(vl, s);
    vfprintf(stdout, s, vl);
    va_end(vl);
}

void errorfunc(HSQUIRRELVM SQ_UNUSED_ARG(v),const SQChar *s,...)
{
    va_list vl;
    va_start(vl, s);
    vfprintf(stderr, s, vl);
    va_end(vl);
}


// Call a Squirrel (ingame script language) function
int callSquirrel(HSQUIRRELVM vm, const char* function){
	int ret;
    sq_pushroottable(vm);
    sq_pushstring(vm,function,-1);
    sq_get(vm,-2); //get the function from the root table
    sq_pushroottable(vm); //'this' (function environment object)
    ret = sq_call(vm,1,SQFalse,SQTrue);
    sq_pop(vm,2); //pops the roottable and the function
	return ret;
}

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

	// init the console
	vramSetBankC(VRAM_C_MAIN_BG_0x06000000);
	consoleInit(0,CONSOLE_BACKGROUND_LAYER, BgType_Text4bpp, BgSize_T_256x256, 31,0, true, true);
	bgHide(CONSOLE_BACKGROUND_LAYER);
    // use VRAM H and I for the keyboard
    videoSetModeSub(MODE_0_2D);
	vramSetBankH(VRAM_H_SUB_BG);
	vramSetBankI(VRAM_I_SUB_BG_0x06208000);
    keyboard = 	keyboardDemoInit();

    //for (int i = 0; i<100; i++) {
    //    printf("HelloWorld");
    //}

    int fovValue = 80;
    Camara = NE_CameraCreate();
    NE_SetFov(fovValue);

    localPlayer.rotation.x = 0;
    localPlayer.rotation.y = 0;
    localPlayer.rotation.z = 0;
    localPlayer.position.x = 0;
    localPlayer.position.y = 0;
    localPlayer.position.z = 0;

    NE_ClippingPlanesSet(0.01, 1000);

    LoadTextures(textureMode);
    //if (Plane->isDrawn)
    //printf("\nplane id:%d\nx1:%.0f x2:%.0f x3:%.0f\ny1:%.0f y2:%.0f y3:%.0f\nz1:%.0f z2:%.0f z3:%.0f\n", Plane->id, Plane->vertex1.x, Plane->vertex1.y, Plane->vertex1.z, Plane->vertex2.x, Plane->vertex2.y, Plane->vertex2.z, Plane->vertex3.x, Plane->vertex3.y, Plane->vertex3.z);

    squirrelvm = sq_open(1024); //creates a VM with initial stack size 1024
    sq_pushroottable(squirrelvm);
    sq_enabledebuginfo(squirrelvm, true);
    sqstd_register_bloblib(squirrelvm);
    sqstd_register_iolib(squirrelvm);
    sqstd_register_systemlib(squirrelvm);
    sqstd_register_mathlib(squirrelvm);
    sqstd_register_stringlib(squirrelvm);
    sqstd_seterrorhandlers(squirrelvm);

    
    //do some stuff with squirrel here
    sq_setprintfunc(squirrelvm, printfunc, errorfunc);
    sqstd_dofile(squirrelvm, "nitro:/scripts/vscripts/hello.nut", false, true);
    
    callSquirrel(squirrelvm, "hi");


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

    Vector3 playerHitboxSize;
    playerHitboxSize.x = 10;
    playerHitboxSize.y = 10;
    playerHitboxSize.z = 10;
    addHitbox(playerHitboxSize, &localPlayer.position, &localPlayer.rotation, 1);

    save();
    // loadLevelVmf("test_map");
    loadLevelBsp("test_map");
    LoadMisc();

    int freemem = NE_TextureFreeMemPercent();
    Vector3 position;
    position.z = 120;
    position.x = 80;
    addCube(position);
    while (1)
    {
        NE_WaitForVBL(NE_UPDATE_ANIMATIONS);

        //FPS counter
        // Get time
        //time_t unixTime = time(NULL);
        //struct tm* timeStruct = gmtime((const time_t*)&unixTime);
        //seconds = timeStruct->tm_sec;
        //
        //// If new second
        //if (seconds != oldsec)
        //{
        //    // Reset fps count and print current
        //    oldsec = seconds;
        //    printf("\x1b[1;20HFPS: %d", fpscount);
        //    fpscount = 0;
        //}


        //printf("\x1b[2;20HVram left:%d", freemem);

        cubes[0].rotation.y += 2;

        //Camera
        // Get keys information
        scanKeys();
        uint32 keys = keysHeld();
        uint32 keys_down = keysDown();


        if (keys & KEY_DOWN){
            localPlayer.physics.velocity.x -= fixedToFloat(sinLerp(floatToFixed(localPlayer.rotation.y / 45, 12)), 13);
            localPlayer.physics.velocity.y -= fixedToFloat(cosLerp(floatToFixed(localPlayer.rotation.y / 45, 12)), 13);
        }
        else if (keys & KEY_UP) {
            localPlayer.physics.velocity.x += fixedToFloat(sinLerp(floatToFixed(localPlayer.rotation.y / 45, 12)), 13);
            localPlayer.physics.velocity.y += fixedToFloat(cosLerp(floatToFixed(localPlayer.rotation.y / 45, 12)), 13);
        }

        if (keys & KEY_LEFT){
            localPlayer.physics.velocity.x += fixedToFloat(cosLerp(floatToFixed(localPlayer.rotation.y / 45, 12)), 13);
            localPlayer.physics.velocity.y -= fixedToFloat(sinLerp(floatToFixed(localPlayer.rotation.y / 45, 12)), 13);
        }
        else if (keys & KEY_RIGHT){
            localPlayer.physics.velocity.x -= fixedToFloat(cosLerp(floatToFixed(localPlayer.rotation.y / 45, 12)), 13);
            localPlayer.physics.velocity.y += fixedToFloat(sinLerp(floatToFixed(localPlayer.rotation.y / 45, 12)), 13);
        }
        
        
        
        if (keys & KEY_A) {
            localPlayer.rotation.y -= 0.0002 * sensitivityHorizontal * fovValue;
        }
        else if (keys & KEY_Y) {
            localPlayer.rotation.y += 0.0002 * sensitivityHorizontal * fovValue;
        }

        if (keys & KEY_B && localPlayer.rotation.z > -88)
        {
            localPlayer.rotation.z -= 0.0002 * sensitivityVertical * fovValue;
        }
        else if (keys & KEY_X && localPlayer.rotation.z < 88)
        {
            localPlayer.rotation.z += 0.0002 * sensitivityVertical * fovValue;
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
            if (keys_down & KEY_R && fovValue > 40)
            {
                fovValue -= 20;
                NE_SetFov(fovValue);
            }

            if (keys_down & KEY_L && fovValue < 80)
            {
                fovValue += 20;
                NE_SetFov(fovValue);
            }

            if (keys & KEY_A && keys & KEY_Y)
            {
                ToggleConsole();
            }
        }
        
        if (keys & KEY_START)
            break;

        //NE_ClearColorSet(NE_White, 31, 63);
        doPhysics();
        NE_Process(Draw3DScene);

        if (isConsoleOpen){
            int keyboardKey = keyboardUpdate();
        }

        // Increase frame count
        fpscount++;
    }

    sq_close(squirrelvm);
    return 0;
}
