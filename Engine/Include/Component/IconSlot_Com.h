#pragma once
#include "UIBase_Com.h"

JEONG_BEGIN

class GameObject;
class Collider_Com;
class UICon_Com;
class JEONG_DLL IconSlot : public UIBase_Com
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	IconSlot* Clone() override;
	void AfterClone() override;
	
	void IconFirst(Collider_Com* Src, Collider_Com* Dest, float DeltaTime);
	void IconHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime);
	void IconOut(Collider_Com* Src, Collider_Com* Dest, float DeltaTime);

private:
	bool m_isOver;
	UICon_Com* m_EquipIcon;

protected:
	IconSlot();
	IconSlot(const IconSlot& CopyData);
	~IconSlot();

public:
	friend class GameObject;
};

JEONG_END
