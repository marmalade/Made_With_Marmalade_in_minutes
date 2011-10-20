/*
 * This file is part of the Marmalade SDK Code Samples.
 *
 * Copyright (C) 2001-2011 Ideaworks3D Ltd.
 * All Rights Reserved.
 *
 * This source code is intended only as a supplement to Ideaworks Labs
 * Development Tools and/or on-line documentation.
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */
#include "s3e.h"
#include "Iw2D.h"
#include "game.h"

// updates per second
#define UPS 60

// throttle frame time at 10 fps (i.e. the game will slow down rather
// than having very low frame rate)
#define MAX_UPDATES 6

int GetUpdateFrame()
{
    return (int)(s3eTimerGetMs() / (1000/UPS));
}

// "main" is the S3E entry point
int main()
{
	Iw2DInit();

    // create game object
    CGame* pGame = new CGame;

	pGame->Init();

    int currentUpdate = GetUpdateFrame();
    int nextUpdate = currentUpdate;

    // to exit correctly, applications should poll for quit requests
	while(!s3eDeviceCheckQuitRequest())
	{
	    // run logic at a fixed frame rate (defined by UPS)
        
        // block until the next frame (don't render unless at 
        // least one update has occurred)
        while(!s3eDeviceCheckQuitRequest())
        {
            nextUpdate = GetUpdateFrame();
            if( nextUpdate != currentUpdate )
                break;
            s3eDeviceYield(1);
        }
        
        // execute update steps
        int frames = nextUpdate - currentUpdate;
        frames = MIN(MAX_UPDATES, frames);
        while(frames--)
        {
            pGame->Update();
        }
        currentUpdate = nextUpdate;
        
        // render the results
        pGame->Render();

		// if an application uses polling input the application 
        // must call update once per frame
        s3ePointerUpdate();
        s3eKeyboardUpdate();

        // S3E applications should yield frequently
		s3eDeviceYield();
	}

	pGame->Terminate();

    // clear up game object
    delete pGame;

	Iw2DTerminate();

	return 0;
}
