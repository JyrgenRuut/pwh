#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <windows.h>
#include <vector>
#include "SHA1.h"
#include "PW.h"
#include "UserIO.h"

using namespace std;

int main()
{
	char siteHash[21];
	char password[27];
	vector<PW> siteList;
	
	UserIO userIO;
	
	userIO.populatePrefsList(siteList);
	userIO.genMasterPasswordHash();
	userIO.getMenu();
	while(1) //main program loop
	{
		switch(userIO.getCommand())
		{
			case CMD_GEN:
				
			case CMD_ADD:
				
			case CMD_PSW:
				userIO.genMasterPasswordHash();
				break;
			case CMD_HLP: case CMD_MNU:
				cout << endl << endl << endl;
				userIO.getMenu();
				break;
			case CMD_MOD:
				
			case CMD_DEL:
				
			case CMD_EXT:
				
			default:
				cout << endl << "Invalid command, please try again!" << endl;
				userIO.getMenu();
		}
	}
	
	return 0;
}



