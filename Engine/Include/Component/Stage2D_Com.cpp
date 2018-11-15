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
	m_isLineOn = true;
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
	Transform_Com* pMainCameraTr = m_Scene->GetMainCameraTransform();
	Vector3	CameraPos = pMainCameraTr->GetWorldPos();
	CameraPos -= m_StartPos;

	Vector3	EndPos = CameraPos;
	EndPos.x += Device::Get()->GetWinSize().Width;
	EndPos.y += Device::Get()->GetWinSize().Height;

	CameraPos /= m_TileScale;
	EndPos /= m_TileScale;

	m_StartX = (int)CameraPos.x;
	if (m_StartX < 0)
		m_StartX = 0;

	else if (m_StartX >= m_TileCountX)
		m_StartX = m_TileCountX - 1;

	m_StartY = (int)CameraPos.y;
	if (m_StartY < 0)
		m_StartY = 0;

	else if (m_StartY >= m_TileCountY)
		m_StartY = m_TileCountY - 1;

	m_EndX = (int)EndPos.x + 1;
	if (m_EndX < 0)
		m_EndX = 0;

	else if (m_EndX >= m_TileCountX)
		m_EndX = m_TileCountX - 1;

	m_EndY = (int)EndPos.y * 2 + 1;
	if (m_EndY < 0)
		m_EndY = 0;

	else if (m_EndY >= m_TileCountY)
		m_EndY = m_TileCountY - 1;

	for (int y = m_StartY; y < m_EndY; ++y)
	{
		for (int x = m_StartX; x < m_EndX; ++x)
		{
			m_vecTileObject[y * m_TileCountX + x]->Update(DeltaTime);
		}
	}

	return 0;
}

int Stage2D_Com::LateUpdate(float DeltaTime)
{
	for (int y = m_StartY; y < m_EndY; ++y)
	{
		for (int x = m_StartX; x < m_EndX; ++x)
		{
			m_vecTileObject[y * m_TileCountX + x]->LateUpdate(DeltaTime);
		}
	}

	return 0;
}

void Stage2D_Com::Collision(float DeltaTime)
{
	for (int y = m_StartY; y < m_EndY; ++y)
	{
		for (int x = m_StartX; x < m_EndX; ++x)
		{
			m_vecTileObject[y * m_TileCountX + x]->Collision(DeltaTime);
		}
	}

}

void Stage2D_Com::CollisionLateUpdate(float DeltaTime)
{
	for (int y = m_StartY; y < m_EndY; ++y)
	{
		for (int x = m_StartX; x < m_EndX; ++x)
		{
			m_vecTileObject[y * m_TileCountX + x]->CollisionLateUpdate(DeltaTime);
		}
	}
}

void Stage2D_Com::Render(float DeltaTime)
{
	for (int y = m_StartY; y < m_EndY; ++y)
	{
		for (int x = m_StartX; x < m_EndX; ++x)
		{
			m_vecTileObject[y * m_TileCountX + x]->Render(DeltaTime);
		}
	}
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

void Stage2D_Com::CreateTileMap(int TileCountX, int TileCountY, const Vector3& StartPos, const Vector3& TileScale, STAGE2D_TILE_TYPE tileType, const string& KeyName, const TCHAR* FileName, const string& PathKey)
{
	for (size_t i = 0; i < m_TileObjectSize; i++)
		SAFE_RELEASE(m_vecTileObject[i]);
	for (size_t i = 0; i < m_TileTransformSize; i++)
		SAFE_RELEASE(m_vecTileTransform[i]);
	for (size_t i = 0; i < m_Tile2DComSize; i++)
		SAFE_RELEASE(m_vecTile2DCom[i]);

	m_StartPos = StartPos;
	m_TileCountX = TileCountX;
	m_TileCountY = TileCountY;

	m_TileObjectCapacity = TileCountX * TileCountY;
	m_TileTransformCapacity = TileCountX * TileCountY;
	m_Tile2DComCapacity = TileCountX * TileCountY;

	m_vecTileObject = new GameObject*[m_TileObjectCapacity];
	m_vecTileTransform = new Transform_Com*[m_TileTransformCapacity];
	m_vecTile2DCom = new Tile2D_Com*[m_Tile2DComCapacity];

	m_TileScale = TileScale;
	m_TileType = tileType;

	//화면 전체크기로 늘린다.
	Vector3 SumScale;
	SumScale.x = TileScale.x * TileCountX;
	SumScale.y = TileScale.y * TileCountY;
	SumScale.z = 1.0f;

	m_Transform->SetWorldPos(StartPos);
	m_Transform->SetWorldScale(SumScale);

	switch (tileType)
	{
		case STT_TILE:
			CreateTile(StartPos, TileScale, KeyName, FileName, PathKey);
			break;
		case STT_ISO:
			CreateIsoTile(StartPos, TileScale, KeyName, FileName, PathKey);
			break;
	}

}

void Stage2D_Com::CreateTile(const Vector3& StartPos, const Vector3& TileScale, const string& KeyName, const TCHAR* FileName, const string& PathKey)
{
	for (int y = 0; y < m_TileCountY; ++y)
	{
		for (int x = 0; x < m_TileCountX; ++x)
		{
			//인덱스공식
			int	Index = y * m_TileCountX + x;

			GameObject*	pTileObject = GameObject::CreateObject("TileObject");
			pTileObject->SetScene(m_Scene);
			pTileObject->SetLayer(m_Layer);

			Tile2D_Com*	pTile = pTileObject->AddComponent<Tile2D_Com>("Tile");
			pTile->SetTileType(STT_TILE);
			pTile->SetLineOn(m_isLineOn);

			Transform_Com*	pTransform = pTileObject->GetTransform();
			pTransform->SetWorldScale(TileScale);

			Vector3	vPos = StartPos + TileScale * Vector3((float)x, (float)y, 1.0f);
			pTransform->SetWorldPos(vPos);

			if (FileName != NULLPTR)
			{
				Renderer_Com* pRenderer = pTileObject->AddComponent<Renderer_Com>("Renderer");
				pRenderer->SetMesh("TextureRect");
				pRenderer->SetRenderState(ALPHA_BLEND);
				SAFE_RELEASE(pRenderer);

				Material_Com* pMaterial = pTileObject->AddComponent<Material_Com>("Material");
				pMaterial->SetDiffuseTexture(0, KeyName, FileName, PathKey);
				SAFE_RELEASE(pMaterial);
			}

			m_vecTileObject[Index] = pTileObject;
			m_vecTileTransform[Index] = pTransform;
			m_vecTile2DCom[Index] = pTile;

			m_TileObjectSize++;
			m_TileTransformSize++;
			m_Tile2DComSize++;

			if (m_TileObjectSize == m_TileObjectCapacity)
			{
				m_TileObjectCapacity *= 2;

				GameObject** newObject = new GameObject*[m_TileObjectCapacity];
				memcpy(newObject, m_vecTileObject, sizeof(m_vecTileObject) * m_TileObjectSize);
				SAFE_DELETE(m_vecTileObject);
				m_vecTileObject = newObject;
			}
			if (m_TileTransformSize == m_TileTransformCapacity)
			{
				m_TileTransformCapacity *= 2;

				Transform_Com** newTr = new Transform_Com*[m_TileObjectCapacity];
				memcpy(newTr, m_vecTileTransform, sizeof(m_vecTileTransform) * m_TileObjectSize);
				SAFE_DELETE(m_vecTileTransform);
				m_vecTileTransform = newTr;

			}
			if (m_Tile2DComSize == m_Tile2DComCapacity)
			{
				m_Tile2DComCapacity *= 2;

				Tile2D_Com** newTile = new Tile2D_Com*[m_Tile2DComCapacity];
				memcpy(newTile, m_vecTile2DCom, sizeof(m_vecTile2DCom) * m_Tile2DComSize);
				SAFE_DELETE(m_vecTile2DCom);
				m_vecTile2DCom = newTile;
			}
		}//for(x)
	}//for(y)
}

void Stage2D_Com::CreateIsoTile(const Vector3& StartPos, const Vector3& TileScale, const string& KeyName , const TCHAR* FileName, const string& PathKey)
{
	for (int y = 0; y < m_TileCountY; y++)
	{
		for (int x = 0; x < m_TileCountY; x++)
		{
			int Index = y * m_TileCountX + x;
			
			GameObject* newTileObject = GameObject::CreateObject("IsoTileObject");
			newTileObject->SetScene(m_Scene);
			newTileObject->SetLayer(m_Layer);

			Tile2D_Com*	pTile = newTileObject->AddComponent<Tile2D_Com>("IsoTile");
			pTile->SetTileType(STT_ISO);

			Transform_Com* pTransform = newTileObject->GetTransform();
			pTransform->SetWorldScale(TileScale);

			Vector3 tPos;
			tPos.x = StartPos.x + (TileScale.x * 0.5f) * (x - y);
			tPos.y = StartPos.y + (TileScale.y * 0.5f) * (x - y);

			pTransform->SetWorldPos(tPos);

			if (FileName != NULLPTR)
			{
				Renderer_Com* pRenderer = newTileObject->AddComponent<Renderer_Com>("Renderer");
				pRenderer->SetMesh("TextureRect");
				pRenderer->SetRenderState(ALPHA_BLEND);
				SAFE_RELEASE(pRenderer);

				Material_Com* pMaterial = newTileObject->AddComponent<Material_Com>("Material");
				pMaterial->SetDiffuseTexture(0, KeyName, FileName, PathKey);
				SAFE_RELEASE(pMaterial);
			}

			m_vecTile2DCom[Index] = pTile;
			m_vecTileTransform[Index] = pTransform;
			m_vecTileObject[Index] = newTileObject;

			m_Tile2DComSize++;
			m_TileTransformSize++;
			m_TileObjectSize++;

			if (m_TileObjectSize == m_TileObjectCapacity)
			{
				m_TileObjectCapacity *= 2;

				GameObject** newObject = new GameObject*[m_TileObjectCapacity];
				memcpy(newObject, m_vecTileObject, sizeof(m_vecTileObject) * m_TileObjectSize);
				SAFE_DELETE(m_vecTileObject);
				m_vecTileObject = newObject;
			}

			if (m_TileTransformSize == m_TileTransformCapacity)
			{
				m_TileTransformCapacity *= 2;

				Transform_Com** newTr = new Transform_Com*[m_TileObjectCapacity];
				memcpy(newTr, m_vecTileTransform, sizeof(m_vecTileTransform) * m_TileObjectSize);
				SAFE_DELETE(m_vecTileTransform);
				m_vecTileTransform = newTr;

			}

			if (m_Tile2DComSize == m_Tile2DComCapacity)
			{
				m_Tile2DComCapacity *= 2;

				Tile2D_Com** newTile = new Tile2D_Com*[m_Tile2DComCapacity];
				memcpy(newTile, m_vecTile2DCom, sizeof(m_vecTile2DCom) * m_Tile2DComSize);
				SAFE_DELETE(m_vecTile2DCom);
				m_vecTile2DCom = newTile;
			}
		}//for(x)
	}//for(y)
}

void Stage2D_Com::SetTileOption(const Vector3& Pos, TILE2D_OPTION option)
{
	int Index = GetTileIndex(Pos);

	if (Index == -1)
		return;

	m_vecTile2DCom[Index]->SetTileOption(option);
}

void Stage2D_Com::SetLineOn(bool Value)
{
	m_isLineOn = Value;

	for (size_t i = 0; i < m_Tile2DComSize; i++)
		m_vecTile2DCom[i]->SetLineOn(m_isLineOn);

}

int Stage2D_Com::GetRectTileIndex(const Vector3 & Pos)
{
	//사각타일 인덱스 구하기. Pos / Size 의 값을 int로 형변환
	int	x = (int)((Pos.x - m_StartPos.x) / m_TileScale.x);

	if (x < 0 || x >= m_TileCountX)
		return -1;

	int	y = (int)((Pos.y - m_StartPos.y) / m_TileScale.y);

	if (y < 0 || y >= m_TileCountY)
		return -1;

	return y * m_TileCountX + x;
}

int Stage2D_Com::GetIsoTileIndex(const Vector3 & Pos)
{
	float 평행이동량 = Pos.y - (Pos.x * 0.5f);
	Vector3 뒤로땡김 = (Pos - 평행이동량);
	뒤로땡김.z = 0.0f;
	
	Vector3 나눈값 = 뒤로땡김 / m_TileScale;
	int 타일인덱스 = (int)(나눈값.y + m_TileCountX + 나눈값.x);

	return 타일인덱스;
}
