#include <nds/arm9/console.h>
#include <nds/arm9/keyboard.h>
#include <stdio.h>
#include "main.h"
#include "console.h"

#define HISTORY_LENGTH 10

char inputBuffer[64];
char inputHistory[HISTORY_LENGTH][64];
int current_history = -1;

typedef void (*commandCallback)(char arguments[4][10]);

typedef struct
{
	char* command; // the command to type
    commandCallback function; // the function to be called
} command;

void Comand_PrintHello(char arguments[4][10]){
    printf("Hello World!");
    if (arguments != NULL) {
        printf("%s", arguments[0]);
    }
}

void Comand_Clear(char arguments[4][10]){
    consoleClear();
}

void Comand_Echo(char arguments[4][10]){
    if (arguments != NULL) {
        printf("%s %s %s %s", arguments[0], arguments[1], arguments[2], arguments[3]);
    }else{
        printf("error, no arguments given");
    }
}

command commands[3] = 
{
    {
        .command = "test",
        .function = Comand_PrintHello,
    },
    {
        .command = "clear",
        .function = Comand_Clear,
    },
    {
        .command = "echo",
        .function = Comand_Echo,
    },
};

void consoleClearLine(){
    printf("\33[2K\r");
}

void OnKeyPressed(int key) {
    if(key > 0){
        //iprintf("%c", key);
        if(key != DVK_ENTER)
            sprintf(inputBuffer, "%s%c", inputBuffer, key); // copy the currently pressed key into the input buffer
    }
    switch (key) {
    case DVK_MENU: // Menu key
        ToggleConsole(); // close the console
        break;
    case DVK_ENTER: // Enter key
        bool foundCommand = false;
        char inputCommand[10] = "";
        char inputArguments[4][10] = {"","","",""};
        sscanf(inputBuffer, "%s %s %s %s %s", inputCommand, inputArguments[0], inputArguments[1], inputArguments[2], inputArguments[3]);
        //if(inputArguments[0][0] == '\"'){ // if arguments start with ", ignore the spaces
        //    sscanf(inputBuffer, "%s%*[^\"]%[^\"] \"%[^\"] %s %s", inputCommand, inputArguments[0], inputArguments[1], inputArguments[2], inputArguments[3]);
        //}
        for(int i = 0; i < sizeof(commands)/sizeof(command); i++){
            if(strcmp(commands[i].command, inputCommand) == 0){ // search evry entry in commands for what was typed
                commands[i].function(inputArguments);
                foundCommand = true;
            }
        }
        if(!foundCommand){
            printf("command \"%s\" not found.\n", inputCommand);
        }
        for(int i = HISTORY_LENGTH - 2; i >= 0; i--){
            for(int j = 0; j < 64; j++){
                inputHistory[i+1][j] = inputHistory[i][j];
            }
        }
        for(int j = 0; j < 64; j++){
            inputHistory[0][j] = inputBuffer[j];
        }
        *inputBuffer = 0;
        current_history = -1;
        break;
    case DVK_UP:
        if(current_history < 10){
            current_history++;
            consoleClearLine();
            for(int j = 0; j < 64; j++){
                inputBuffer[j] = inputHistory[current_history][j];
            }
            printf(inputBuffer);
        }
        break;
    case DVK_DOWN:
        if(current_history >= 0){
            current_history--;
            consoleClearLine();
            for(int j = 0; j < 64; j++){
                inputBuffer[j] = inputHistory[current_history][j];
            }
            printf(inputBuffer);
        }
        break;
    }
    

}

void OpenConsole(void)
{
	bgShow(CONSOLE_BACKGROUND_LAYER);

    // set the callback
    keyboard->OnKeyPressed = OnKeyPressed;

	keyboardShow();

}


void CloseConsole(void)
{
	keyboardHide();
	bgHide(CONSOLE_BACKGROUND_LAYER);
    // unset the callback
    keyboard->OnKeyPressed = NULL;
}

void ToggleConsole(void)
{
    if(isConsoleOpen){
        CloseConsole();
    }else{
        OpenConsole();
    }
    isConsoleOpen = !isConsoleOpen;
}