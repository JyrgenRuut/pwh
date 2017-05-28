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
	char password[27];
	vector<PW> siteList;
	
	UserIO userIO;
	
	userIO.populatePrefsList(siteList);
	userIO.genHash(GEN_TYPE_MASTER_PASSWORD);
	userIO.getMenu();
	while(1) //main program loop
	{
		switch(userIO.getCommand())
		{
			case CMD_GEN:
				userIO.genHash(GEN_TYPE_SITE);
				userIO.genPassword(siteList);
				break;
			case CMD_ADD:
				
			case CMD_PSW:
				userIO.genHash(GEN_TYPE_MASTER_PASSWORD);
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



