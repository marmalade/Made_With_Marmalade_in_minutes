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

#include "IwGx.h"

CGame::CGame():
m_Width(0),
m_Height(0),
m_GameOver(false)
{
}


CGame::~CGame()
{
}


void CGame::Init()
{
	m_Width = IwGxGetScreenWidth();
	m_Height = IwGxGetScreenHeight();

	Ball.SetImage("./textures/Ball.bmp");
	Ball.SetSize(CIwSVec2(30,30));
	Ball.SetPosition(CIwSVec2(100,100));
	Ball.SetVelocity(CIwSVec2(-2,-2));

	Paddle.SetImage("./textures/Paddle.bmp");
	Paddle.SetSize(CIwSVec2(120,10));
	Paddle.SetPosition(CIwSVec2(m_Width/2,m_Height - 15));
}

void CGame::Update()
{    
    // game logic goes here
	if(!m_GameOver)
	{
		Ball.Update();

		if (s3ePointerGetState(S3E_POINTER_BUTTON_SELECT) & S3E_POINTER_STATE_DOWN )
			Paddle.SetPositionX(s3ePointerGetX());

		if(Ball.GetPosition()->x + (Ball.GetSize()->y/2) > m_Width)
		{
			Ball.SetPositionX((m_Width - (Ball.GetSize()->x/2)));
			Ball.SetVelocityX(Ball.GetVelocity()->x *-1);
		}
		else if(Ball.GetPosition()->x - (Ball.GetSize()->x/2) < 0)
		{
			Ball.SetPositionX(Ball.GetSize()->x/2);
			Ball.SetVelocityX(Ball.GetVelocity()->x *-1);
		}
		
		if(Ball.GetPosition()->y - (Ball.GetSize()->y/2) < 0)
		{
			Ball.SetPositionY(Ball.GetSize()->y/2);
			Ball.SetVelocityY(Ball.GetVelocity()->y *-1);
		}
		else if(Ball.GetPosition()->y + (Ball.GetSize()->y/2) > Paddle.GetPosition()->y - (Paddle.GetSize()->y/2))
		{
			if(Ball.GetPosition()->x > Paddle.GetPosition()->x - (Paddle.GetSize()->x/2) &&
				Ball.GetPosition()->x < Paddle.GetPosition()->x + (Paddle.GetSize()->x/2))
			{
				Ball.SetPositionY(Paddle.GetPosition()->y - (Paddle.GetSize()->y/2) - (Ball.GetSize()->x/2));
				Ball.SetVelocityY(Ball.GetVelocity()->y *-1);
			}
			else
			{
				m_GameOver = true;
			}
		}
	}

	else
	{
		//Restart new game
		if (s3ePointerGetState(S3E_POINTER_BUTTON_SELECT) & S3E_POINTER_STATE_PRESSED )
		{
			m_GameOver = false;
			Ball.SetPosition(CIwSVec2(100,100));
			Ball.SetVelocity(CIwSVec2(-2,-2));
		}
	}
}


void CGame::Render()
{
    // game render goes here
	if(!m_GameOver)
	{
		Iw2DSurfaceClear(0xffffffff);
		Ball.Render();
		Paddle.Render();
	}
	else
		Iw2DSurfaceClear(0xff000000);

    // show the surface
    Iw2DSurfaceShow();
}

void CGame::Terminate()
{
}
