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

#include "s3eTypes.h"
#include "Iw2D.h"

class CIw2DSprite
{
private:
    CIwSVec2	m_Position;
    CIwSVec2	m_Velocity;
	CIwSVec2	m_Size;
	CIw2DImage*	m_p2DImage;


	void CleanUp(void);

public:
	CIw2DSprite(void);
	CIw2DSprite(CIwSVec2 size);
	~CIw2DSprite(void);

    void Update();
    void Render();

	// ---- Setter(s) ----------------------------------------------------
	void SetPosition(CIwSVec2 position){ m_Position = position; };
	void SetPositionX(int16 x){ m_Position.x = x; };
	void SetPositionY(int16 y){ m_Position.y = y; };

	void SetVelocity(CIwSVec2 velocity){ m_Velocity = velocity; };
	void SetVelocityX(int16 x){ m_Velocity.x = x; };
	void SetVelocityY(int16 y){ m_Velocity.y = y; };

	void SetSize(CIwSVec2 size);
	void SetImage(const char* filename);

	// ---- Getter(s) ----------------------------------------------------
	const CIwSVec2* GetPosition(void){ return &m_Position; };
	const CIwSVec2* GetVelocity(void){ return &m_Velocity; };
	const CIwSVec2* GetSize(void) { return &m_Size; };
};
