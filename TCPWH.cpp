#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "SHA1.h"
#include "PW.h"
#include "UserIO.h"

using namespace std;

int main()
{
	char masterPasswordHash[21];
	char siteHash[21];
	char password[27];
	UserIO userIO;
	
	userIO.getMasterPasswordHash(masterPasswordHash);
	userIO.getMenu();
	while(1) //main program loop
	{
		
	}
	
	return 0;
}



