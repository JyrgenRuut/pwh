#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <windows.h>
#include "SHA1.h"
#include "PW.h"
#include "UserIO.h"

using namespace std;

int main()
{
	vector<PW> siteList;
	
	UserIO userIO;
	
	userIO.populatePrefsList(siteList);
	userIO.genHash(GEN_TYPE_MASTER_PASSWORD);
	userIO.printMenu();
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
				userIO.printMenu();
				break;
			case CMD_MOD:
				userIO.genHash(GEN_TYPE_SITE);
				userIO.modifyPref(siteList);
				break;
			case CMD_DEL:
				userIO.genHash(GEN_TYPE_SITE);
				userIO.deletePrefsListEntry(siteList);
				break;
			case CMD_EXT:
				userIO.savePrefs(siteList);
				return 0;
				break;
			default:
				cout << endl << "Invalid command, please try again!" << endl;
				userIO.printMenu();
		}
	}
	
	return 0;
}



