#ifndef WIFI_H
#define WIFI_H

extern char* palletteFilePath;
extern char* iconFilePath;
extern char pallette[32];
extern char icon[512];
extern int arm9Size;
extern int arm7Size;
extern int arm9Offset;
extern int arm7Offset;


extern unsigned char WIFI_Buffer[1024];
extern u16 sendBufferData[254];
extern u8 bufferData9[0xE7534];
extern u8 bufferData7[0x289A4];
extern int wifiChannel;
extern unsigned short tempSendBuffer[78];
extern int WIFI_ReceivedDataLength;		// Size of data received from the wifi
extern u16 secondDeviceMAC[3];
extern char username[10];
extern unsigned int usernameLength;
extern unsigned int userTheme;
extern unsigned int StreamCode;
extern char title[48];
extern char description[96];
extern int maxPlayers;


extern u16 beaconNum;
extern u16 beaconNumArm7Started;

void loadIcon();

void initDownloadPlay();

//void SendDownloadPlay();

void WirelessHandler(int packetID, int readlength);
#endif