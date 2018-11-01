#pragma once
#include "CheckBox_Com.h"

JEONG_BEGIN

class CheckBox_Com;
class GameObject;
class JEONG_DLL RadioButton_Com : public CheckBox_Com
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	RadioButton_Com* Clone() override;
	void AfterClone() override;

protected:
	RadioButton_Com();
	RadioButton_Com(const RadioButton_Com& CopyDaa);
	~RadioButton_Com();

public:
	friend class GameObject;
};

JEONG_END
  