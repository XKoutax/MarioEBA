#include "DarkGDK.h"

#include "globstruct.h" //FOR MESSAGE BOX

void DarkGDK()
{
	dbSyncOn();
	dbSyncRate(60);
	dbSetDisplayMode(800, 600, 32);
	//dbMaximizeWindow();
	dbBackdropOn();
	dbBackdropColor(dbRGB(0, 255, 0));
	

	while (LoopGDK())
	{



		dbSync();


	}
	return;
}