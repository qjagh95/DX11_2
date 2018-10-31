#include "RadioButton_Com.h"

JEONG_USING

RadioButton_Com::RadioButton_Com()
{
}

RadioButton_Com::RadioButton_Com(const RadioButton_Com & CopyData)
	:Button_Com(CopyData)
{
}

RadioButton_Com::~RadioButton_Com()
{
}

bool RadioButton_Com::Init()
{
	return true;
}

int RadioButton_Com::Input(float DeltaTime)
{
	return 0;
}

int RadioButton_Com::Update(float DeltaTime)
{
	return 0;
}

int RadioButton_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void RadioButton_Com::Collision(float DeltaTime)
{
}

void RadioButton_Com::CollisionLateUpdate(float DeltaTime)
{
}

void RadioButton_Com::Render(float DeltaTime)
{
}

RadioButton_Com * RadioButton_Com::Clone()
{
	return new RadioButton_Com(*this);
}

void RadioButton_Com::AfterClone()
{
}
