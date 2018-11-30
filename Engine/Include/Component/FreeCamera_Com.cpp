#include "stdafx.h"
#include "FreeCamera_Com.h"

JEONG_USING

FreeCamera_Com::FreeCamera_Com()
{
}

FreeCamera_Com::FreeCamera_Com(const FreeCamera_Com & CopyData)
	:Component_Base(CopyData)
{
}


FreeCamera_Com::~FreeCamera_Com()
{
}

bool FreeCamera_Com::Init()
{
	KeyInput::Get()->AddKey("CameraUp", VK_UP);
	KeyInput::Get()->AddKey("CameraDown", VK_DOWN);
	KeyInput::Get()->AddKey("CameraLeft", VK_LEFT);
	KeyInput::Get()->AddKey("CameraRight", VK_RIGHT);

	m_Speed = 1000.0f;
	return true;
}

int FreeCamera_Com::Input(float DeltaTime)
{
	return 0;
}

int FreeCamera_Com::Update(float DeltaTime)
{
	if (KeyInput::Get()->KeyPress("CameraUp"))
		m_Transform->Move(AXIS_Y, m_Speed, DeltaTime);
	else if (KeyInput::Get()->KeyPress("CameraDown"))
		m_Transform->Move(AXIS_Y, -m_Speed, DeltaTime);

	if (KeyInput::Get()->KeyPress("CameraLeft"))
		m_Transform->Move(AXIS_X, -m_Speed, DeltaTime);
	else if (KeyInput::Get()->KeyPress("CameraRight"))
		m_Transform->Move(AXIS_X, m_Speed, DeltaTime);

	return 0;
}

int FreeCamera_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void FreeCamera_Com::Collision(float DeltaTime)
{
}

void FreeCamera_Com::Render(float DeltaTime)
{
}

FreeCamera_Com * FreeCamera_Com::Clone()
{
	return new FreeCamera_Com(*this);
}
