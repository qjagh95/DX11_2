#include "stdafx.h"
#include "BackColor_Com.h"

JEONG_USING

BackColor_Com::BackColor_Com()
{
}

BackColor_Com::BackColor_Com(const BackColor_Com & CopyData)
	:UIBase_Com(CopyData)
{
	*this = CopyData;
}

BackColor_Com::~BackColor_Com()
{
}

bool BackColor_Com::Init()
{
	return true;
}

int BackColor_Com::Input(float DeltaTime)
{
	return 0;
}

int BackColor_Com::Update(float DeltaTime)
{
	return 0;
}

int BackColor_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void BackColor_Com::Collision(float DeltaTime)
{
}

void BackColor_Com::CollisionLateUpdate(float DeltaTime)
{
}

void BackColor_Com::Render(float DeltaTime)
{
}

BackColor_Com * BackColor_Com::Clone()
{
	return new BackColor_Com(*this);
}

void BackColor_Com::AfterClone()
{
}
