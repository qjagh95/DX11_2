#pragma once
#include <Scene/SceneComponent.h>
#include <Component/BackColor_Com.h>
#include <Component/Stage2D_Com.h>

class EditScene : public SceneComponent
{
public:
	bool Init() override;
	int Update(float DeltaTime) override;

private:
	BackColor_Com* m_BackColorCom;

public:
	EditScene();
	~EditScene();
};

