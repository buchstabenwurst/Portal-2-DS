#include <fat.h>
#include <dirent.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

FILE* savefile;
void save() {
	char saveText[512];
	savefile = fopen("fat:/_nds/PortalDS/save.sav", "wb");
	sprintf(saveText, "test lol");
	fwrite(saveText, 1, strlen(saveText), savefile);
	fclose(savefile);
}