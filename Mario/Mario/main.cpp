#include "DarkGDK.h"
#include "globstruct.h" //USED FOR MESSAGE box 



void DarkGDK()
{
	dbSyncOn();
	dbSyncRate(60);
	dbSetDisplayMode(800, 600, 32);
	//dbMaximizeWindow();
	dbBackdropOn();
	dbBackdropColor(dbRGB(0, 255, 0));
	
	load.loadImages();
	load.loadCurrentLevel(level);
	load.loadSounds();

	while (LoopGDK())
	{
		mapping.playSounds();
		mapping.displayLevel();
		mapping.displayInformation();

		dbSync();
	}
	return;
}