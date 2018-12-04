#include "stdafx.h"
#include "TileImage_Com.h"

JEONG_USING

TileImage_Com::TileImage_Com()
{
}

TileImage_Com::TileImage_Com(const TileImage_Com & CopyData)
	:Component_Base(CopyData)
{
}

TileImage_Com::~TileImage_Com()
{
}

bool TileImage_Com::Init()
{
	//Renderer_Com* a;
	//Material_Com * b;

	return true;
}

int TileImage_Com::Input(float DeltaTime)
{
	return 0;
}

int TileImage_Com::Update(float DeltaTime)
{
	return 0;
}

int TileImage_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void TileImage_Com::Collision(float DeltaTime)
{
}

void TileImage_Com::CollisionLateUpdate(float DeltaTime)
{
}

void TileImage_Com::Render(float DeltaTime)
{
}

TileImage_Com * TileImage_Com::Clone()
{
	return new TileImage_Com(*this);
}

void TileImage_Com::AfterClone()
{
}

void TileImage_Com::Save(BineryWrite & Writer)
{
	Component_Base::Save(Writer);
}

void TileImage_Com::Load(BineryRead & Reader)
{
	Component_Base::Load(Reader);

}
