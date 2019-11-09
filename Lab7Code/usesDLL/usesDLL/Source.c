/*
Name: Russell Harvey
*/

#include <stdio.h>
#include <windows.h>
#include <string.h>

typedef void (*myfun1_t)(char[], char[]);
typedef void (*myfun2_t)(char[]);
typedef void (*myfun3_t)(char[], char[]);

/*
This is the main loop for the user shell.
Uses SampleDLL.
*/
void main(void)
{
	myfun1_t myfun1;
	myfun2_t myfun2;
	myfun3_t myfun3;
	HINSTANCE mydll = LoadLibrary("C:\\Users\\Russell\\Desktop\\RIT\\Programming for Info. Security\\Lab7Code\\sampleDLL\\x64\\Debug\\sampleDLL.dll");
	while (1) {
		char cmd[10];
		int lightswitch;
		printf("user>> ");
		scanf_s("%s", cmd, 10);

		if (strncmp(cmd, "exit", 4) == 0) {
			exit(0);
		}
		else if (strncmp(cmd, "1", 1) == 0) {
			lightswitch = 1;
		}
		else if (strncmp(cmd, "2", 1) == 0) {
			lightswitch = 2;
		}
		else if (strncmp(cmd, "3", 1) == 0) {
			lightswitch = 3;
		}
		else if (strncmp(cmd, "4", 1) == 0) {
			lightswitch = 0;
			STARTUPINFO si;
			PROCESS_INFORMATION pi;
			ZeroMemory(&pi, sizeof(pi));
			ZeroMemory(&si, sizeof(si));
			char user4[20];
			char params[60];
			printf("Username: ");
			scanf_s("%s", user4, 20);
			printf("\tUsername is %s\n", user4);
			sprintf_s(params, 60, "net user %s", user4);
			if (!CreateProcess(NULL, params, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
				printf("CreateProcess Failed (%d).\n", GetLastError());
				return;
			}
			else {
				WaitForSingleObject(pi.hProcess, INFINITE);
				CloseHandle(pi.hThread);
				CloseHandle(pi.hProcess);
			}
			system("pause");
		}
		else if (strncmp(cmd, "help", 4) == 0) {
			lightswitch = 0;
			printf("Please enter one of the following\n(1) Add User\n(2) Delete User\n(3) Change Password\n(4) View User\n(exit) Exit Program\n");
			system("pause");
		}
		else {
			lightswitch = 0;
			printf("Enter 'help' to view a list of commands\n");
			system("pause");
		}

		switch (lightswitch) {
		case 1:
			printf("---Add User---\n");
			char user[20];
			char pass[20];
			printf("Username: ");
			scanf_s("%s", user, 20);
			printf("\tUsername is %s\n", user);
			printf("Password: ");
			scanf_s("%s", pass, 20);
			printf("\tPassword is %s\n", pass);
			myfun1 = (myfun1_t)GetProcAddress(mydll, "addUser");
			myfun1(user, pass);
			system("pause");
			break;
		case 2:
			printf("---Delete User---\n");
			char user2[20];
			printf("Username: ");
			scanf_s("%s", user2, 20);
			printf("\tUsername is %s\n", user2);
			myfun2 = (myfun2_t)GetProcAddress(mydll, "delUser");
			myfun2(user2);
			system("pause");
			break;
		case 3:
			printf("---Change Password---\n");
			char user3[20];
			char pass3[20];
			printf("Username: ");
			scanf_s("%s", user3, 20);
			printf("\tUsername is %s\n", user3);
			printf("New Password: ");
			scanf_s("%s", pass3, 20);
			printf("\tNew Password is %s\n", pass3);
			myfun3 = (myfun3_t)GetProcAddress(mydll, "chPass");
			myfun3(user3, pass3);
			system("pause");
			break;
		default:
			break;
		}
		system("cls");
	}
}