#include "Iw2DSprite.h"

CIw2DSprite::CIw2DSprite(void):
m_Velocity(0,0),
m_Position(0,0),
m_Size(20, 20),
m_p2DImage(NULL)
{
}

CIw2DSprite::CIw2DSprite(CIwSVec2 size):
m_Velocity(0,0),
m_Position(0,0),
m_Size(size),
m_p2DImage(NULL)
{
	SetSize(size);
}

CIw2DSprite::~CIw2DSprite(void)
{
	CleanUp();
}


void CIw2DSprite::Update(void)
{
	m_Position += m_Velocity;
}

void CIw2DSprite::Render()
{
	Iw2DDrawImage(m_p2DImage, m_Position - CIwSVec2(m_Size.x/2,m_Size.y/2), m_Size); 
}


void CIw2DSprite::SetSize(CIwSVec2 size)
{
	m_Size = size;
}

void CIw2DSprite::SetImage(const char* filename)
{
	CleanUp();

	m_p2DImage = Iw2DCreateImage(filename);
}


void CIw2DSprite::CleanUp(void)
{
	if(m_p2DImage)
		delete m_p2DImage;

	m_p2DImage = NULL;
}