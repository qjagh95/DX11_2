#pragma once
#include "../stdafx.h"
JEONG_BEGIN

class RenderState;
class BlendState;
class JEONG_DLL RenderManager
{
public:
	bool Init();

	void AddBlendTargetDesc(BOOL bEnable, D3D11_BLEND srcBlend = D3D11_BLEND_SRC_ALPHA, D3D11_BLEND destBlend = D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP blendOp = D3D11_BLEND_OP_ADD, D3D11_BLEND srcAlphaBlend = D3D11_BLEND_ONE, D3D11_BLEND destAlphaBlend = D3D11_BLEND_ZERO, D3D11_BLEND_OP blendAlphaOp = D3D11_BLEND_OP_ADD, UINT8 iWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL);
	bool CreateDepthStencilState(const string& KeyName, BOOL bDepthEnable, D3D11_DEPTH_WRITE_MASK eMask = D3D11_DEPTH_WRITE_MASK_ALL, D3D11_COMPARISON_FUNC eDepthFunc = D3D11_COMPARISON_LESS, BOOL bStencilEnable = FALSE, UINT8 iStencilReadMask = 0, UINT8 iStencilWriteMask = 0, D3D11_DEPTH_STENCILOP_DESC tFrontFace = {}, D3D11_DEPTH_STENCILOP_DESC tBackFace = {});
	bool CreateBlendState(const string& KeyName, BOOL bAlphaCoverage = FALSE, BOOL bIndependent = FALSE);
	void SetGameMode(GAME_MODE eMode) { m_GameMode = eMode; }
	GAME_MODE GetGameMode() const { return m_GameMode; }

	RenderState* FindRenderState(const string& KeyName);

private:
	GAME_MODE m_GameMode;

	unordered_map<string, RenderState*> m_RenderStateMap;
	BlendState* m_CreateState;	

public:
	CLASS_IN_SINGLE(RenderManager)
};

JEONG_END

