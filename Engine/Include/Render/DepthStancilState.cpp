#include "DepthStancilState.h"
#include "../Device.h"

JEONG_USING

DepthStancilState::DepthStancilState()
{
	m_StencilRef = 0xffffffff;
	m_State = RS_DEPTHSTENCIL;
}

DepthStancilState::~DepthStancilState()
{
}

bool DepthStancilState::CreateState(BOOL bDepthEnable, D3D11_DEPTH_WRITE_MASK eMask, D3D11_COMPARISON_FUNC eDepthFunc, BOOL bStencilEnable, UINT8 iStencilReadMask, UINT8 iStencilWriteMask, D3D11_DEPTH_STENCILOP_DESC tFrontFace, D3D11_DEPTH_STENCILOP_DESC tBackFace)
{
	D3D11_DEPTH_STENCIL_DESC depthDesc;
	depthDesc.DepthEnable = bDepthEnable;			//±íÀÌ¹öÆÛ »ç¿ëÇÒ²¨ÀÓ?
	depthDesc.DepthWriteMask = eMask;				//ALL(¾²±â»ç¿ë), ZERO(²û)
	depthDesc.DepthFunc = eDepthFunc;				//¿¬»êÀÚ
	depthDesc.StencilEnable = bStencilEnable;		//½ºÅÄ½Ç »ç¿ëÇÒ²¨?
	depthDesc.StencilReadMask = iStencilReadMask; 
	depthDesc.StencilWriteMask = iStencilWriteMask;
	depthDesc.FrontFace = tFrontFace;
	depthDesc.BackFace = tBackFace;

	if (FAILED(Device::Get()->GetDevice()->CreateDepthStencilState(&depthDesc, (ID3D11DepthStencilState**)&m_RenderState)))
		return false;

	return true;
}

void DepthStancilState::SetState()
{
	Device::Get()->GetContext()->OMGetDepthStencilState((ID3D11DepthStencilState**)&m_OldRenderState, &m_OldStencilRef);
	Device::Get()->GetContext()->OMSetDepthStencilState((ID3D11DepthStencilState*)m_RenderState, m_StencilRef);
}

void DepthStancilState::ResetState()
{
	Device::Get()->GetContext()->OMSetDepthStencilState((ID3D11DepthStencilState*)m_OldRenderState, m_OldStencilRef);
	SAFE_RELEASE(m_OldRenderState);
}