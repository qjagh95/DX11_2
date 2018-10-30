#pragma once
#include "Button_Com.h"

JEONG_BEGIN
class JEONG_DLL CheckBox_Com : public Button_Com
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	CheckBox_Com* Clone() override;
	void AfterClone() override;

	void Check(float DeltaTime);

private:
	CHECKBOX_STATE m_CheckState;

protected:
	CheckBox_Com();
	CheckBox_Com(const CheckBox_Com& CopyData);
	~CheckBox_Com();

public:
	friend class GameObject;
};

JEONG_END