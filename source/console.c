#include <nds/arm9/console.h>
#include <nds/arm9/keyboard.h>
#include <stdio.h>
#include "main.h"
#include "console.h"

char inputBuffer[64];

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
        printf("%s", arguments[0]);
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

void OnKeyPressed(int key) {
    if(key > 0){
        iprintf("%c", key);
        if(key != DVK_ENTER)
            sprintf(inputBuffer, "%s%c", inputBuffer, key); // copy the currently pressed key into the input buffer
    }
    switch (key) {
    case DVK_MENU: // Menu key
        ToggleConsole(); // close the console
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
        *inputBuffer = 0;
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