#include "CheckBox_Com.h"
#include "Renderer_Com.h"
#include "Material_Com.h"

#include "../GameObject.h"

JEONG_USING

CheckBox_Com::CheckBox_Com()
{
	m_UIType = UT_CHECKBOX;
	m_CheckState = CBS_FALSE;
}

CheckBox_Com::CheckBox_Com(const CheckBox_Com & CopyData) : Button_Com(CopyData)
{
}

CheckBox_Com::~CheckBox_Com()
{
}

bool CheckBox_Com::Init()
{
	Button_Com::Init();
	SetCallBack(&CheckBox_Com::Check, this);

	return true;
}

int CheckBox_Com::Input(float DeltaTime)
{
	Button_Com::Input(DeltaTime);

	return 0;
}

int CheckBox_Com::Update(float DeltaTime)
{
	Button_Com::Update(DeltaTime);

	if (m_CheckState == CBS_TRUE)
	{
		Material_Com* getCom = FindComponentFromType<Material_Com>(CT_MATERIAL);
		getCom->SetMaterial(Vector4::Brown);
		SAFE_RELEASE(getCom);
	}

	else if (m_CheckState == CBS_FALSE)
	{
		Material_Com* getCom = FindComponentFromType<Material_Com>(CT_MATERIAL);
		getCom->SetMaterial(Vector4::White);
		SAFE_RELEASE(getCom);
	}
	return 0;
}

int CheckBox_Com::LateUpdate(float DeltaTime)
{
	Button_Com::LateUpdate(DeltaTime);

	return 0;
}

void CheckBox_Com::Collision(float DeltaTime)
{
	Button_Com::Collision(DeltaTime);
}

void CheckBox_Com::CollisionLateUpdate(float DeltaTime)
{
	Button_Com::CollisionLateUpdate(DeltaTime);
}

void CheckBox_Com::Render(float DeltaTime)
{
	Button_Com::Render(DeltaTime);
}

CheckBox_Com * CheckBox_Com::Clone()
{
	return new CheckBox_Com(*this);
}

void CheckBox_Com::AfterClone()
{
}

void CheckBox_Com::Check(float DeltaTime)
{
	if (m_CheckState == CBS_TRUE)
		m_CheckState = CBS_FALSE;

	else if(m_CheckState == CBS_FALSE)
		m_CheckState = CBS_TRUE;
}
