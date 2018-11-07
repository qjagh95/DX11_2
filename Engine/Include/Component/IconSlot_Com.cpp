#include "IconSlot_Com.h"
#include "Renderer_Com.h"
#include "Material_Com.h"
#include "ColliderPoint_Com.h"
#include "Animation2D_Com.h"
#include "Transform_Com.h"
#include "UICon_Com.h"

#include "../GameObject.h"
#include "../KeyInput.h"

JEONG_USING

IconSlot_Com::IconSlot_Com()
{
	m_UIType = UT_ICONSLOT;
	SetTag("IconSlot");
	m_isOver = false;
	m_EquipIcon = NULLPTR;
}

IconSlot_Com::IconSlot_Com(const IconSlot_Com & CopyData)
	:UIBase_Com(CopyData)
{
}

IconSlot_Com::~IconSlot_Com()
{
	SAFE_RELEASE(m_EquipIcon);
}

bool IconSlot_Com::Init()
{
	Renderer_Com* RenderComponent = m_Object->AddComponent<Renderer_Com>("IconSlotRender");
	RenderComponent->SetMesh("TextureRect");
	RenderComponent->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(RenderComponent);

	Material_Com* MaterialComponent = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	MaterialComponent->SetDiffuseTexture(0, "IconSlot", TEXT("IconSlot.png"));
	SAFE_RELEASE(MaterialComponent);

	ColliderPoint_Com* RectColl = m_Object->AddComponent<ColliderPoint_Com>("IconSlotBody");
	RectColl->SetInfo(Vector3(0.0f, 15.0f, 0.0f));
	RectColl->SetCollsionCallback(CCT_DOING, this, &IconSlot_Com::IconHit);
	RectColl->SetCollsionCallback(CCT_END, this, &IconSlot_Com::IconOut);
	RectColl->SetCollisionGroup("UI");
	RectColl->SetMyTypeName("IconSlot");
	RectColl->PushContinueTypeName("IconSlot");
	RectColl->PushContinueTypeName("MouseWindow");
	RectColl->PushContinueTypeName("MouseWorld");

	m_Transform->SetWorldPivot(0.5f, 0.0f, 0.0f);
	m_Transform->SetWorldScale(30.0f, 30.0f, 0.0f);

	return true;
}

int IconSlot_Com::Input(float DeltaTime)
{
	if (m_isOver == true)
	{
		if (KeyInput::Get()->KeyUp("LButton"))
		{
			if (m_EquipIcon != NULLPTR)
			{
				m_EquipIcon->GetTransform()->SetWorldPos(m_Transform->GetWorldPos());
				SAFE_RELEASE(m_EquipIcon);
			}

		}
	}

	return 0;
}

int IconSlot_Com::Update(float DeltaTime)
{
	return 0;
}

int IconSlot_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void IconSlot_Com::Collision(float DeltaTime)
{
}

void IconSlot_Com::CollisionLateUpdate(float DeltaTime)
{
}

void IconSlot_Com::Render(float DeltaTime)
{
}

IconSlot_Com * IconSlot_Com::Clone()
{
	return new IconSlot_Com(*this);
}

void IconSlot_Com::AfterClone()
{
}

void IconSlot_Com::IconHit(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "UIconBody")
	{
		m_isOver = true;
	}
}

void IconSlot_Com::IconOut(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "UIconBody")
	{
		m_isOver = false;
	}
}
