#pragma once
#include "UIBase_Com.h"

JEONG_BEGIN

class IconSlot_Com;
class Collider_Com;
class JEONG_DLL UICon_Com : public UIBase_Com
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	UICon_Com* Clone() override;
	void AfterClone() override;

	void Active();
	void SetSlotEquip(bool Value) { m_SlotEquip = Value; }
	bool GetSlotEquip() const { return m_SlotEquip; }
	
	void MouseHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime);
	void MouseOut(Collider_Com* Src, Collider_Com* Dest, float DeltaTime);

private:
	bool m_isOver;
	bool m_isMove;
	bool m_SlotEquip;
	bool m_isSwap;
	IconSlot_Com* m_mySlot;

protected:
	UICon_Com();
	UICon_Com(const UICon_Com& CopyDaa);
	~UICon_Com();

public:
	friend class GameObject;
};

JEONG_END
