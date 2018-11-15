#include "stdafx.h"
#include "Tile2D_Com.h"

JEONG_USING

Tile2D_Com::Tile2D_Com()
{
	m_ComType = CT_STAGE2D;
	SetTag("Stage2D");
}
Tile2D_Com::Tile2D_Com(const Tile2D_Com& CopyData)
	:Component_Base(CopyData)
{
	*this = CopyData;
}

Tile2D_Com::~Tile2D_Com()
{
}

bool Tile2D_Com::Init()
{
	return true;
}

int Tile2D_Com::Input(float DeltaTime)
{
	return 0;
}

int Tile2D_Com::Update(float DeltaTime)
{
	return 0;
}

int Tile2D_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Tile2D_Com::Collision(float DeltaTime)
{
}

void Tile2D_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Tile2D_Com::Render(float DeltaTime)
{
}

Tile2D_Com * Tile2D_Com::Clone()
{
	return new Tile2D_Com(*this);
}

void Tile2D_Com::AfterClone()
{
}
