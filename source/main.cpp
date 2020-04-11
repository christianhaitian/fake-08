

#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphics.h"
#include "fakecart.h"
#include "picointernals.h"

int main(int argc, char* argv[])
{
	int frames = 0; 
	gfxInitDefault();

	initPicoInternals();

	consoleInit(GFX_BOTTOM, NULL);
	
	// Main loop
	while (aptMainLoop())
	{
		gspWaitForVBlank();

		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) break; // break in order to return to hbmenu

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();
		
		_update();
		
		uint8_t* fb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
		//clear whole framebuffer
		memset(fb, 192, 240*400*3);

		//cart draw
		_draw();

		//send pico 8 screen to framebuffer
		flipBuffer(fb);

    	frames++;
	}

	gfxExit();
	return 0;
}