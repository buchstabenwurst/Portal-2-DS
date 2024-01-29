#include <nds.h>
#include <dswifi9.h>
#include <stdio.h>
#include <memory.h>
#include "wifi.h"
#include "main.h"

FILE* palletteFile;
FILE* iconFile;
char* palletteFilePath = "nitro:/Icon.nbfp";
char* iconFilePath = "nitro:/Icon.nbfc";

unsigned char WIFI_Buffer[1024];			// Wifi buffer is the incoming data from the wifi (DO NOT USE LIKE THIS, please use the "wirelessData" define)
#define wirelessData (WIFI_Buffer + 32) // Define to use the WIFI_Buffer array to avoid wrong values
int WIFI_ReceivedDataLength = 0;		// Size of data received from the wifi
u16 secondDeviceMAC[3];
u16 sendBufferData[254];
u8 bufferData9[0xE7534];
u8 bufferData7[0x289A4];

int wifiChannel = 7;
unsigned short tempSendBuffer[78];
char username[10] = "";
unsigned int usernameLength = 0;
unsigned int userTheme = 0;
unsigned int StreamCode = 0xABCD;
char title[48] = "Download Play Example by Buchstabenwurst";
char description[96] = "https://github.com/buchstabenwurst\nBeschreibung, wow\x00""lol";
int maxPlayers = 16;

char pallette[32];
char icon[512];
int arm9Size;
int arm7Size;
int arm9Offset;
int arm7Offset;

u16 beaconNum = 0;
u16 beaconNumArm7Started = 0;

void loadIcon(void) {
    palletteFile = fopen(palletteFilePath, "rb");
    fread(pallette, 1, 32, palletteFile);
    fclose(palletteFile);

    iconFile = fopen(iconFilePath, "rb");
    fread(icon, 1, 512, iconFile);
    fclose(iconFile);
}

void initDownloadPlay() {
    timerStart(0, ClockDivider_1024, TIMER_FREQ_1024(5), SendDownloadPlay);
}

void treatData()
{
    // Get data lenght
    int recvd_len = strlen(wirelessData);

    // printf("%s\n", wirelessData);

    // Check if the packet is valid
    if (WIFI_ReceivedDataLength == recvd_len + 1)
    {
        printf("%x", wirelessData);
    }
}

void WirelessHandler(int packetID, int readlength)
{
    Wifi_RxRawReadPacket(packetID, readlength, (unsigned short*)WIFI_Buffer);

    WIFI_ReceivedDataLength = readlength - 32;

    // is probably Authentication Request
    if (readlength == 30) {
        timerStop(0);

        secondDeviceMAC[0] = Wifi_RxReadOffset(WIFI_ReceivedDataLength, 13);
        secondDeviceMAC[1] = Wifi_RxReadOffset(WIFI_ReceivedDataLength, 14);
        secondDeviceMAC[2] = Wifi_RxReadOffset(WIFI_ReceivedDataLength, 15);
        //printf("\x1b[4;2H%x", secondDeviceMAC[0]);
        //printf("\x1b[4;6H%x", secondDeviceMAC[1]);
        //printf("\x1b[4;10H%x",secondDeviceMAC[2]);

        //memset(tempSendBuffer, 0x00, sizeof(tempSendBuffer));
        //tempSendBuffer[];
        //Wifi_Multiboot_Init();
        Wifi_SendAuthenticationResponse(secondDeviceMAC);
    }
    if (readlength == 66) {

        //secondDeviceMAC[0] = Wifi_RxReadOffset(WIFI_ReceivedDataLength, 13);
        //secondDeviceMAC[1] = Wifi_RxReadOffset(WIFI_ReceivedDataLength, 14);
        //secondDeviceMAC[2] = Wifi_RxReadOffset(WIFI_ReceivedDataLength, 15);
        printf("\x1b[4;2H%x", secondDeviceMAC[0]);
        printf("\x1b[4;6H%x", secondDeviceMAC[1]);
        printf("\x1b[4;10H%x", secondDeviceMAC[2]);

        Wifi_SendAssociationResponse(secondDeviceMAC);

        //username Request

        Wifi_SendMultibootData(6, 0, 1);

        // username Done
        Wifi_SendMultibootData(6, 0, 0);
        timerStart(0, ClockDivider_1024, TIMER_FREQ_1024(5),Wifi_SendFakeCmdAck);

        }
    //if ()

    printf("\x1b[21;20H%d", readlength);
    printf("\x1b[5;20H%x", wirelessData[0]);
    printf("\x1b[6;20H%x", WIFI_Buffer[10]);
    printf("\x1b[7;20H%x", WIFI_Buffer[11]);
    printf("\x1b[8;20H%x", WIFI_Buffer[12]);
    printf("\x1b[9;20H%x", Wifi_RxReadOffset(WIFI_ReceivedDataLength, -1));
    printf("\x1b[10;20H%x", Wifi_RxReadOffset(WIFI_ReceivedDataLength, 10));
    printf("\x1b[11;20H%x", Wifi_RxReadOffset(WIFI_ReceivedDataLength, 11));
    printf("\x1b[12;20H%x", Wifi_RxReadOffset(WIFI_ReceivedDataLength, 12));
    printf("\x1b[13;20H%x", Wifi_RxReadOffset(WIFI_ReceivedDataLength, 13));
    printf("\x1b[14;20H%x", Wifi_RxReadOffset(WIFI_ReceivedDataLength, 14));
    printf("\x1b[15;20H%x", Wifi_RxReadOffset(WIFI_ReceivedDataLength, 15));
    printf("\x1b[16;20H%x", Wifi_RxReadOffset(WIFI_ReceivedDataLength, 16));
    printf("\x1b[17;20H%x", Wifi_RxReadOffset(WIFI_ReceivedDataLength, 17));
    printf("\x1b[18;20H%x", Wifi_RxReadOffset(WIFI_ReceivedDataLength, 18));
    printf("\x1b[19;20H%x", Wifi_RxReadOffset(WIFI_ReceivedDataLength, 19));

    // Treatment of the data
    treatData();
}