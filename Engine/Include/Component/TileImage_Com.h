#pragma once
#include "Component_Base.h"

JEONG_BEGIN

class JEONG_DLL TileImage_Com : public Component_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	TileImage_Com* Clone() override;
	void AfterClone() override;
	void Save(BineryWrite& Writer) override;
	void Load(BineryRead& Reader) override;

protected:
	TileImage_Com();
	TileImage_Com(const TileImage_Com& CopyData);
	~TileImage_Com();

public:
	friend class GameObject;
};

JEONG_END

