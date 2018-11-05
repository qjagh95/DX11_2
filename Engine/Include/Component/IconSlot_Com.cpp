#include "IconSlot_Com.h"
#include "Renderer_Com.h"
#include "Material_Com.h"
#include "ColliderRect_Com.h"
#include "Animation2D_Com.h"
#include "Transform_Com.h"
#include "UICon_Com.h"

#include "../GameObject.h"
#include "../KeyInput.h"

JEONG_USING

IconSlot::IconSlot()
{
	m_UIType = UT_ICONSLOT;
	SetTag("IconSlot");
	m_isOver = false;
	m_EquipIcon = NULLPTR;
}

IconSlot::IconSlot(const IconSlot & CopyData)
	:UIBase_Com(CopyData)
{
}

IconSlot::~IconSlot()
{
	SAFE_RELEASE(m_EquipIcon);
}

bool IconSlot::Init()
{
	Renderer_Com* RenderComponent = m_Object->AddComponent<Renderer_Com>("IconSlotRender");
	RenderComponent->SetMesh("TextureRect");
	RenderComponent->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(RenderComponent);

	Material_Com* MaterialComponent = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	MaterialComponent->SetDiffuseTexture(0, "IconSlot", TEXT("IconSlot.png"));
	SAFE_RELEASE(MaterialComponent);

	ColliderRect_Com* RectColl = m_Object->AddComponent<ColliderRect_Com>("IconSlotBody");
	RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(50.0f, 50.0f, 0.0f));
	RectColl->SetCollsionCallback(CCT_DOING, this, &IconSlot::IconHit);
	RectColl->SetCollsionCallback(CCT_END, this, &IconSlot::IconOut);
	RectColl->SetCollisionGroup("UI");

	m_Transform->SetWorldPivot(0.5f, 0.0f, 0.0f);

	return true;
}

int IconSlot::Input(float DeltaTime)
{
	return 0;
}

int IconSlot::Update(float DeltaTime)
{
	if (m_isOver == true && m_EquipIcon != NULLPTR)
	{
		if (KeyInput::Get()->KeyUp("LButton"))
		{

		}
	}

	return 0;
}

int IconSlot::LateUpdate(float DeltaTime)
{
	return 0;
}

void IconSlot::Collision(float DeltaTime)
{
}

void IconSlot::CollisionLateUpdate(float DeltaTime)
{
}

void IconSlot::Render(float DeltaTime)
{
}

IconSlot * IconSlot::Clone()
{
	return new IconSlot(*this);
}

void IconSlot::AfterClone()
{
}

void IconSlot::IconFirst(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "UIconBody")
	{
		m_EquipIcon = (UICon_Com*)Dest->FindComponentFromType<UIBase_Com>(CT_UI);
	}
}

void IconSlot::IconHit(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "UIconBody")
	{
		m_isOver = true;
	}
}

void IconSlot::IconOut(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "UIconBody")
	{
		m_isOver = false;
		SAFE_RELEASE(m_EquipIcon);
	}
}
