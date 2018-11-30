#pragma once
#include "Component_Base.h"

JEONG_BEGIN

class GameObject;
class Transform_Com;
class Tile2D_Com;
class JEONG_DLL Stage2D_Com : public Component_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	Stage2D_Com* Clone() override;
	void AfterClone() override;

	void SetStageTileType(STAGE2D_TILE_TYPE TileType) { m_TileType = TileType; }
	STAGE2D_TILE_TYPE GetStageTileType() const { return m_TileType; }
	void SetTileOption(const Vector3& Pos, enum TILE2D_OPTION option);
	void SetNoMoveMesh(const Vector3& Pos);
	void SetMoveMesh(const Vector3& Pos);

	int GetTileIndex(const Vector3& Pos);
	int GetRectTileIndex(const Vector3& Pos);
	int GetIsoTileIndex(const Vector3& Pos);
	Vector2 GetIsoTileIndexVec(const Vector3& Pos);
	void SetLineOn(bool Value);

	void CreateTileMap(int TileCountX, int TileCountY, const Vector3& StartPos, const Vector3& TileScale, STAGE2D_TILE_TYPE tileType, const string& KeyName = "", const TCHAR* FileName = NULLPTR, const string& PathKey = TEXTURE_PATH);

private:
	void CreateTile(const Vector3& StartPos, const Vector3& TileScale, const string& KeyName = "", const TCHAR* FileName = NULLPTR,	const string& PathKey = TEXTURE_PATH);
	void CreateIsoTile(const Vector3& StartPos, const Vector3& TileScale, const string& KeyName = "", const TCHAR* FileName = NULLPTR, const string& PathKey = TEXTURE_PATH);

private:
	GameObject** m_vecTileObject;
	Tile2D_Com** m_vecTile2DCom;

	int m_TileObjectCapacity;
	int m_TileObjectSize;
	int m_Tile2DComCapacity;
	int m_Tile2DComSize;

	int m_TileCountX;
	int m_TileCountY;

	STAGE2D_TILE_TYPE m_TileType;

	Vector3 m_TileScale;
	Vector3 m_StartPos;

	bool m_isLineOn;
	int	m_StartX;
	int	m_StartY;
	int	m_EndX;
	int	m_EndY;

protected:
	Stage2D_Com();
	Stage2D_Com(const Stage2D_Com& CopyData);
	~Stage2D_Com();

public:
	friend class GameObject;
};

JEONG_END

