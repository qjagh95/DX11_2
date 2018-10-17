#include "RenderManager.h"
#include "ShaderManager.h"
#include "BlendState.h"
#include "DepthStancilState.h"

JEONG_USING
SINGLETON_VAR_INIT(RenderManager)

RenderManager::RenderManager()
	:m_CreateState(NULLPTR)
{
	m_GameMode = GM_3D;
}

RenderManager::~RenderManager()
{
	ShaderManager::Delete();
	Safe_Release_Map(m_RenderStateMap);
}

bool RenderManager::Init()
{
	if (ShaderManager::Get()->Init() == false)
	{
		TrueAssert(true);
		return false;
	}

	AddBlendTargetDesc(TRUE);
	CreateBlendState(ALPHA_BLEND);
	CreateDepthStencilState(DEPTH_DISABLE, FALSE);

	return true;
}

void RenderManager::AddBlendTargetDesc(BOOL bEnable, D3D11_BLEND srcBlend, D3D11_BLEND destBlend, D3D11_BLEND_OP blendOp, D3D11_BLEND srcAlphaBlend, D3D11_BLEND destAlphaBlend, D3D11_BLEND_OP blendAlphaOp, UINT8 iWriteMask)
{
	if (m_CreateState == NULLPTR)
		m_CreateState = new BlendState();

	m_CreateState->AddTargetDesc(bEnable, srcBlend, destBlend,blendOp, srcAlphaBlend, destAlphaBlend, blendAlphaOp,iWriteMask);
}

bool RenderManager::CreateDepthStencilState(const string & KeyName, BOOL bDepthEnable, D3D11_DEPTH_WRITE_MASK eMask, D3D11_COMPARISON_FUNC eDepthFunc, BOOL bStencilEnable, UINT8 iStencilReadMask, UINT8 iStencilWriteMask, D3D11_DEPTH_STENCILOP_DESC tFrontFace, D3D11_DEPTH_STENCILOP_DESC tBackFace)
{
	DepthStancilState* newState = (DepthStancilState*)FindRenderState(KeyName);

	if (newState != NULLPTR)
		return false;

	newState = new DepthStancilState();

	if (newState->CreateState(bDepthEnable, eMask, eDepthFunc, bStencilEnable, iStencilReadMask, iStencilWriteMask, tFrontFace, tBackFace) == false)
	{
		SAFE_RELEASE(newState);
		return false;
	}

	m_RenderStateMap.insert(make_pair(KeyName, newState));

	return true;
}

bool RenderManager::CreateBlendState(const string & KeyName, BOOL bAlphaCoverage, BOOL bIndependent)
{
	if (m_CreateState == NULLPTR)
		return false;

	if (m_CreateState->CreateState(bAlphaCoverage, bIndependent) == false)
	{
		SAFE_RELEASE(m_CreateState);
		return false;
	}

	m_RenderStateMap.insert(make_pair(KeyName, m_CreateState));
	m_CreateState = NULLPTR;

	return true;
}

RenderState * RenderManager::FindRenderState(const string & KeyName)
{
	unordered_map<string, RenderState*>::iterator FindIter = m_RenderStateMap.find(KeyName);

	if (FindIter == m_RenderStateMap.end())
		return NULLPTR;

	return FindIter->second;
}
