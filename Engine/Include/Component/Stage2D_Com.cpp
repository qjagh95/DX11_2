#include "stdafx.h"
#include "Stage2D_Com.h"
#include "Tile2D_Com.h"

JEONG_USING

Stage2D_Com::Stage2D_Com()
	:m_vecTile2DCom(NULLPTR), m_vecTileObject(NULLPTR), m_vecTileTransform(NULLPTR),
	m_TileObjectCapacity(10), m_TileObjectSize(0), m_TileTransformCapacity(10), m_TileTransformSize(0), m_Tile2DComCapacity(10), m_Tile2DComSize(0)
{
	m_ComType = CT_TILE2D;
	SetTag("Stage2D");
}
Stage2D_Com::Stage2D_Com(const Stage2D_Com& CopyData)
	:Component_Base(CopyData)
{
	*this = CopyData;
}

Stage2D_Com::~Stage2D_Com()
{
	for (size_t i = 0; i < m_TileObjectSize; i++)
		SAFE_RELEASE(m_vecTileObject[i]);
	for (size_t i = 0; i < m_TileTransformSize; i++)
		SAFE_RELEASE(m_vecTileTransform[i]);
	for (size_t i = 0; i < m_Tile2DComSize; i++)
		SAFE_RELEASE(m_vecTile2DCom[i]);
}

bool Stage2D_Com::Init()
{
	return true;
}

int Stage2D_Com::Input(float DeltaTime)
{
	return 0;
}

int Stage2D_Com::Update(float DeltaTime)
{
	return 0;
}

int Stage2D_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Stage2D_Com::Collision(float DeltaTime)
{
}

void Stage2D_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Stage2D_Com::Render(float DeltaTime)
{
}

Stage2D_Com * Stage2D_Com::Clone()
{
	return new Stage2D_Com(*this);
}

void Stage2D_Com::AfterClone()
{
}

int Stage2D_Com::GetTileIndex(const Vector3 & Pos)
{
	switch (m_TileType)
	{
		case STT_TILE:
			return GetRectTileIndex(Pos);
			break;
		case STT_ISO:
			return GetIsoTileIndex(Pos);
			break;
	}
	return -1;
}

int Stage2D_Com::GetRectTileIndex(const Vector3 & Pos)
{
	int	x = (int)((Pos.x - m_StartPos.x) / m_TileScale.x);
	if (x < 0 || x >= m_NumX)
		return -1;

	int	y = (int)((Pos.y - m_StartPos.y) / m_TileScale.y);
	if (y < 0 || y >= m_NumY)
		return -1;

	return y * m_NumX + x;
}

int Stage2D_Com::GetIsoTileIndex(const Vector3 & Pos)
{
	return 0;
}

void Stage2D_Com::CreateTileMap(int NumX, int NumY, const Vector3 & StartPos, const Vector3 & TileScale, STAGE2D_TILE_TYPE tileType)
{
	for (size_t i = 0; i < m_TileObjectSize; i++)
		SAFE_RELEASE(m_vecTileObject[i]);
	for (size_t i = 0; i < m_TileTransformSize; i++)
		SAFE_RELEASE(m_vecTileTransform[i]);
	for (size_t i = 0; i < m_Tile2DComSize; i++)
		SAFE_RELEASE(m_vecTile2DCom[i]);

	m_StartPos = StartPos;
	m_NumX = NumX;
	m_NumY = NumY;

	m_TileObjectCapacity = NumX * NumY;
	m_TileTransformCapacity = NumX * NumY;
	m_Tile2DComCapacity = NumX * NumY;

	m_vecTileObject = new GameObject*[m_TileObjectCapacity];
	m_vecTileTransform = new Transform_Com*[m_TileTransformCapacity];
	m_vecTile2DCom = new Tile2D_Com*[m_Tile2DComCapacity];

	m_TileScale = TileScale;
	m_TileType = tileType;

	//화면 전체크기로 늘린다.
	Vector3 SumScale;
	SumScale.x = TileScale.x * NumX;
	SumScale.y = TileScale.y * NumY;
	SumScale.z = 1.0f;

	m_Transform->SetWorldPos(StartPos);
	m_Transform->SetWorldScale(SumScale);

	switch (tileType)
	{
		case STT_TILE:
			CreateTile(StartPos, TileScale);
			break;
		case STT_ISO:
			CreateIsoTile(StartPos, TileScale);
			break;
	}

}

void Stage2D_Com::CreateTile(const Vector3 & StartPos, const Vector3 & TileScale)
{
	for (int y = 0; y < m_NumY; ++y)
	{
		for (int x = 0; x < m_NumX; ++x)
		{
			//인덱스공식
			int	Index = y * m_NumX + x;

			GameObject*	pTileObject = GameObject::CreateObject("TileObject");
			Tile2D_Com*	pTile = pTileObject->AddComponent<Tile2D_Com>("Tile");
			Transform_Com*	pTransform = pTileObject->GetTransform();
			pTransform->SetWorldScale(TileScale);

			Vector3	vPos = StartPos + TileScale * Vector3((float)x, (float)y, 1.0f);
			pTransform->SetWorldPos(vPos);

			m_vecTileObject[Index] = pTileObject;
			m_vecTileTransform[Index] = pTransform;
			m_vecTile2DCom[Index] = pTile;

			m_TileObjectSize++;
			m_TileTransformSize++;
			m_Tile2DComSize++;
		}
	}
}

void Stage2D_Com::CreateIsoTile(const Vector3 & StartPos, const Vector3 & TileScale)
{
}

void Stage2D_Com::SetTileOption(const Vector3& Pos, TILE2D_OPTION option)
{
	int Index = GetTileIndex(Pos);

	if (Index == -1)
		return;

	m_vecTile2DCom[Index]->SetTileOption(option);
}