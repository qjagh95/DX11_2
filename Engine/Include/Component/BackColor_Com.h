#pragma once
#include "UIBase_Com.h"

JEONG_BEGIN

class JEONG_DLL BackColor_Com : public UIBase_Com
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	BackColor_Com* Clone() override;
	void AfterClone() override;

protected:
	BackColor_Com();
	BackColor_Com(const BackColor_Com& CopyData);
	~BackColor_Com();
};

JEONG_END

