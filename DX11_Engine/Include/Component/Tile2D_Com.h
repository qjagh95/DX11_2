#pragma once
#include "Component_Base.h"

JEONG_BEGIN

enum TILE2D_OPTION
{
	T2D_NORMAL,
	T2D_NOMOVE,
};

class Tile2D_Com : public Component_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	Tile2D_Com* Clone() override;
	void AfterClone() override;

	TILE2D_OPTION GetTileOption() const { return m_TileOption; }
	void SetTileOption(TILE2D_OPTION option) { m_TileOption = option; }

private:
	TILE2D_OPTION m_TileOption;

protected:
	Tile2D_Com();
	Tile2D_Com(const Tile2D_Com& CopyData);
	~Tile2D_Com();

public:
	friend class GameObject;
};

JEONG_END