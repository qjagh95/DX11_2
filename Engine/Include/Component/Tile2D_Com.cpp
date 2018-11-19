#include "stdafx.h"
#include "Tile2D_Com.h"
#include "../Resource/Mesh.h"
#include "../Render/Shader.h"

JEONG_USING

Tile2D_Com::Tile2D_Com()
	:m_Shader(NULLPTR), m_Mesh(NULLPTR), m_Layout(NULLPTR)
{
	m_ComType = CT_STAGE2D;
	SetTag("Stage2D");
	m_isLine = true;
}

Tile2D_Com::Tile2D_Com(const Tile2D_Com& CopyData)
	:Component_Base(CopyData)
{
	*this = CopyData;
}

Tile2D_Com::~Tile2D_Com()
{
	SAFE_RELEASE(m_Mesh);
	SAFE_RELEASE(m_Shader);
}

bool Tile2D_Com::Init()
{
	m_TileOption = T2D_NORMAL;
	m_Mesh = ResourceManager::Get()->FindMesh("IsoTileNomal");
	m_Shader = ShaderManager::Get()->FindShader(TILE_SHADER);

	return true;
}

int Tile2D_Com::Input(float DeltaTime)
{
	return 0;
}

int Tile2D_Com::Update(float DeltaTime)
{
	return 0;
}

int Tile2D_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Tile2D_Com::Collision(float DeltaTime)
{
}

void Tile2D_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Tile2D_Com::Render(float DeltaTime)
{
	if (m_isLine == false)
		return;

	TransformCBuffer tCBuffer = {};
	Camera_Com*	pMainCamera = m_Scene->GetMainCamera();

	tCBuffer.World = m_Transform->GetWorldMatrix();
	tCBuffer.View = pMainCamera->GetViewMatrix();
	tCBuffer.Projection = pMainCamera->GetProjection();
	tCBuffer.WV = tCBuffer.World * tCBuffer.View;
	tCBuffer.WVP = tCBuffer.WV * tCBuffer.Projection;
	tCBuffer.Pivot = Vector3::Zero;
	tCBuffer.Lenth = m_Mesh->GetLenth();

	tCBuffer.World.Transpose();
	tCBuffer.View.Transpose();
	tCBuffer.Projection.Transpose();
	tCBuffer.WV.Transpose();
	tCBuffer.WVP.Transpose();

	ShaderManager::Get()->UpdateCBuffer("Transform", &tCBuffer);

	Vector4	LineColor;
	switch (m_TileOption)
	{
		case T2D_NORMAL:
			LineColor = Vector4::Green;
			break;
		case T2D_NOMOVE:
			LineColor = Vector4::Red;
			break;
	}

	m_Shader->SetShader();
	{
		Device::Get()->GetContext()->IASetInputLayout(m_Layout);
		ShaderManager::Get()->UpdateCBuffer("Collider", &LineColor);
	}
	m_Mesh->Render();
}

Tile2D_Com * Tile2D_Com::Clone()
{
	return new Tile2D_Com(*this);
}

void Tile2D_Com::AfterClone()
{
}

void Tile2D_Com::SetTileType(STAGE2D_TILE_TYPE type)
{
	m_TileType = type;
	
	SAFE_RELEASE(m_Mesh);
	SAFE_RELEASE(m_Shader);

	switch (type)
	{
		case STT_TILE:
			m_Mesh = ResourceManager::Get()->FindMesh("ColliderRect");
			break;
		case STT_ISO:
			m_Mesh = ResourceManager::Get()->FindMesh("IsoTileNomal");
			break;
	}

	m_Shader = ShaderManager::Get()->FindShader(TILE_SHADER);
	m_Layout = ShaderManager::Get()->FindInputLayOut(POS_LAYOUT);
}
