#ifndef WIFI_H
#define WIFI_H

extern char* palletteFilePath;
extern char* iconFilePath;
extern char pallette[32];
extern char icon[512];

extern int wifiChannel;
extern unsigned short tempSendBuffer[78];
extern char username[10];
extern unsigned int usernameLength;
extern unsigned int userTheme;
extern char title[48];
extern char description[96];
extern int maxPlayers;


extern int beaconNum;

void loadIcon();

void initDownloadPlay();

void SendDownloadPlay();

#endif