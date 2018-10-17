#pragma once
#include "RenderState.h"

JEONG_BEGIN

//이클래스는 2D 3D모드에따라서 모든 오브젝트들에게 하나씩 깊이버퍼를 사용하거나, 사용하지 않을것을 
//디바이스에 알리기위한것이다.
class DepthStancilState : public RenderState
{
public:
	bool CreateState(BOOL bDepthEnable, D3D11_DEPTH_WRITE_MASK eMask = D3D11_DEPTH_WRITE_MASK_ALL, D3D11_COMPARISON_FUNC eDepthFunc = D3D11_COMPARISON_LESS, BOOL bStencilEnable = FALSE, UINT8 iStencilReadMask = 0, UINT8 iStencilWriteMask = 0, D3D11_DEPTH_STENCILOP_DESC tFrontFace = {}, D3D11_DEPTH_STENCILOP_DESC tBackFace = {});

	void SetState() override;
	void ResetState() override;

private:
	UINT m_StencilRef;
	UINT m_OldStencilRef;

private:
	DepthStancilState();
	~DepthStancilState();

public:
	friend class RenderManager;
};

JEONG_END