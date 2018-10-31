#include "Bar_Com.h"
#include "Renderer_Com.h"
#include "Material_Com.h"
#include "ColliderRect_Com.h"
#include "Animation2D_Com.h"
#include "Transform_Com.h"

#include "../GameObject.h"

JEONG_USING

Bar_Com::Bar_Com()
{
	m_UIType = UT_BAR;
	SetTag("Bar");
}

Bar_Com::Bar_Com(const Bar_Com & CopyData)
	:Button_Com(CopyData)
{
	m_Dir = CopyData.m_Dir;
	m_MinValue = CopyData.m_MinValue;
	m_MaxValue = CopyData.m_MaxValue;
	m_Value = CopyData.m_Value;
}

Bar_Com::~Bar_Com()
{
}

bool Bar_Com::Init()
{
	//일단 기본셋팅.
	m_Dir = BD_LEFT;

	m_MinValue = 0.0f;
	m_MaxValue = 100.0f;
	m_Value = 100.0f;

	return true;
}

int Bar_Com::Input(float DeltaTime)
{
	return 0;
}

int Bar_Com::Update(float DeltaTime)
{
	return 0;
}

int Bar_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Bar_Com::Collision(float DeltaTime)
{
}

void Bar_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Bar_Com::Render(float DeltaTime)
{
}

Bar_Com * Bar_Com::Clone()
{
	return new Bar_Com(*this);
}

void Bar_Com::AfterClone()
{
}

void Bar_Com::SetDir(BAR_DIR dir)
{
	m_Dir = dir;

	//줄어드는 방향에 따라서 피봇을 조정한다.
	switch (m_Dir)
	{
		case BD_LEFT:
			m_Transform->SetWorldPivot(0.0f, 0.0f, 0.0f);
			break;
		case BD_RIGHT:
			m_Transform->SetWorldPivot(1.0f, 0.0f, 0.0f);
			break;
		case BD_UP:
			m_Transform->SetWorldPivot(0.0f, 1.0f, 0.0f);
			break;
		case BD_DOWN:
			m_Transform->SetWorldPivot(0.0f, 0.0f, 0.0f);
			break;
	}
}

void Bar_Com::AddValue(float Value)
{
	m_Value += Value;

	if (m_Value < m_MinValue)
		m_Value = m_MinValue;

	else if (m_Value > m_MaxValue)
		m_Value = m_MaxValue;
}

void Bar_Com::SetMinMaxValue(float minValue, float maxValue)
{
	m_MinValue = minValue;
	m_MaxValue = maxValue;

	if (m_Value < m_MinValue)
		m_Value = m_MinValue;

	else if (m_Value > m_MaxValue)
		m_Value = m_MaxValue;

}

