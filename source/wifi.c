#include <nds.h>
#include <dswifi9.h>
#include <stdio.h>
#include <memory.h>
#include "wifi.h"

FILE* palletteFile;
FILE* iconFile;
char* palletteFilePath = "nitro:/Icon.nbfp";
char* iconFilePath = "nitro:/Icon.nbfc";

int wifiChannel = 7;
unsigned short tempSendBuffer[78];
char username[10] = "";
unsigned int usernameLength = 0;
unsigned int userTheme = 0;
char title[48] = "Download Play Example by Buchstabenwurst";
char description[96] = "https://github.com/buchstabenwurst\nBeschreibung, wow\x00""lol";
int maxPlayers = 16;

char pallette[32];
char icon[512];

int beaconNum = 0;

void loadIcon(void) {
    palletteFile = fopen(palletteFilePath, "rb");
    fread(pallette, 1, 32, palletteFile);
    fclose(palletteFile);

    iconFile = fopen(iconFilePath, "rb");
    fread(icon, 1, 512, iconFile);
    fclose(iconFile);
}

void initDownloadPlay() {
    
}
