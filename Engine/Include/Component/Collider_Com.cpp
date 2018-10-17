#include "Collider_Com.h"

#include "../Device.h"

#include "../Resource/Mesh.h"
#include "../Resource/ResourceManager.h"

#include "../Render/Shader.h"
#include "../Render/ShaderManager.h"
#include "../Render/RenderManager.h"
#include "../Render/RenderState.h"

JEONG_USING

Collider_Com::Collider_Com()
{
	m_CollType = CT_RECT;
	m_ComType = CT_COLLIDER;
	m_CollisionGroupName = "Default";
	m_UpdateCollision = true;

#ifdef _DEBUG
	m_Shader = ShaderManager::Get()->FindShader(COLLIDER_SHADER);
	m_LayOut = ShaderManager::Get()->FindInputLayOut(POS_LAYOUT);
	m_Mesh = NULLPTR;
	m_DepthDisable = NULLPTR;
	m_Color = Vector4::Green;

#endif // _DEBUG
}

Collider_Com::Collider_Com(const Collider_Com & CopyCollider)
	:Component_Base(CopyCollider)
{
	*this = CopyCollider;

#ifdef _DEBUG
	m_LayOut = CopyCollider.m_LayOut;
	m_Mesh = CopyCollider.m_Mesh;
	m_Shader = CopyCollider.m_Shader;
	m_DepthDisable = CopyCollider.m_DepthDisable;
	m_Color = Vector4::Green;

	if (m_Shader)
		m_Shader->AddRefCount();

	if (m_Mesh)
		m_Mesh->AddRefCount();

	if (m_DepthDisable)
		m_DepthDisable->AddRefCount();
#endif // _DEBUG

}

Collider_Com::~Collider_Com()
{
#ifdef _DEBUG
	SAFE_RELEASE(m_DepthDisable);
	SAFE_RELEASE(m_Shader);
	SAFE_RELEASE(m_Mesh);
#endif

	list<Collider_Com*>::iterator StartIter = m_PrevCollision.begin();
	list<Collider_Com*>::iterator EndIter = m_PrevCollision.end();

	for (; StartIter != EndIter; StartIter++)
	{
		OnCollsionEnd(*StartIter, 0.0f);
		(*StartIter)->OnCollsionEnd(this, 0.0f);
		(*StartIter)->ErasePrevCollision(this);
	}
}

bool Collider_Com::Init()
{
	return true;
}

int Collider_Com::Input(float DeltaTime)
{  
	return 0;
}

int Collider_Com::Update(float DeltaTime)
{
	return 0;
}

int Collider_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Collider_Com::Collision(float DeltaTime)
{
}

void Collider_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Collider_Com::Render(float DeltaTime)
{
#ifdef _DEBUG
	if (m_PrevCollision.empty() == true)
		m_Color = Vector4::Green;
	else
		m_Color = Vector4::Red;

	m_Shader->SetShader();
	Device::Get()->GetContext()->IAGetInputLayout(&m_LayOut);

	ShaderManager::Get()->UpdateCBuffer("Collider", &m_Color);

	if (m_DepthDisable != NULLPTR)
		m_DepthDisable->SetState();

	m_Mesh->Render();

	if (m_DepthDisable != NULLPTR)
		m_DepthDisable->ResetState();
#endif

}

bool Collider_Com::CheckPrevCollision(Collider_Com * Dest)
{
	list<Collider_Com*>::iterator StartIter = m_PrevCollision.begin();
	list<Collider_Com*>::iterator EndIter = m_PrevCollision.end();

	for (; StartIter != EndIter; StartIter++)
	{
		if ((*StartIter) == Dest)
			return true;
	}

	return false;
}

void Collider_Com::ErasePrevCollision(Collider_Com * Dest)
{
	list<Collider_Com*>::iterator StartIter = m_PrevCollision.begin();
	list<Collider_Com*>::iterator EndIter = m_PrevCollision.end();

	for (; StartIter != EndIter; StartIter++)
	{
		if ((*StartIter) == Dest)
		{
			m_PrevCollision.erase(StartIter);
			return;
		}
	}
}

void Collider_Com::CheckPrevCollisionInSection(float DeltaTime)
{
	list<Collider_Com*>::iterator StartIter = m_PrevCollision.begin();
	list<Collider_Com*>::iterator EndIter = m_PrevCollision.end();

	for (; StartIter != EndIter; )
	{
		//속해있는 그룹이 같지않으면 End함수호출 후 이전컬라이더를 지운다.
		if (m_CollisionGroupName != (*StartIter)->m_CollisionGroupName)
		{
			OnCollsionEnd((*StartIter), DeltaTime);
			(*StartIter)->OnCollsionEnd(this, DeltaTime);

			(*StartIter)->ErasePrevCollision(this);
			StartIter = m_PrevCollision.erase(StartIter);

			EndIter = m_PrevCollision.end();
			continue;
		}

		const list<int>* getSectionIndex = (*StartIter)->GetSectionIndexList();
		list<int>::const_iterator StartIter1 = getSectionIndex->begin();
		list<int>::const_iterator EndIter1 = getSectionIndex->end();

		list<int>::iterator	StartIter2 = m_SelectionIndexList.begin();
		list<int>::iterator	EndIter2 = m_SelectionIndexList.end();

		bool bPair = false;

		for (; StartIter1 != EndIter1; ++StartIter1)
		{
			//속한 공간의 인덱스가 같다면 넘어감.
			for (; StartIter2 != EndIter2; ++StartIter2)
			{
				if (*StartIter1 == *StartIter2)
				{
					bPair = true;
					break;
				}
			}

			if (bPair == true)
				break;
		}

		if (bPair == false)
		{
			OnCollsionEnd((*StartIter), DeltaTime);
			(*StartIter)->OnCollsionEnd(this, DeltaTime);

			(*StartIter)->ErasePrevCollision(this);
			StartIter = m_PrevCollision.erase(StartIter);

			EndIter = m_PrevCollision.end();
			continue;
		}
		++StartIter;
	}
}

void Collider_Com::OnCollsionFirst(Collider_Com * Dest, float DeltaTime)
{
	list<function<void(Collider_Com*, Collider_Com*, float)>>::iterator	StartIter = m_CollisionFunc[CCT_FIRST].begin();
	list<function<void(Collider_Com*, Collider_Com*, float)>>::iterator	EndIter = m_CollisionFunc[CCT_FIRST].end();

	//함수포인터 실행
	for (; StartIter != EndIter; ++StartIter)
		(*StartIter)(this, Dest, DeltaTime);
}

void Collider_Com::OnCollsionDoing(Collider_Com * Dest, float DeltaTime)
{
	list<function<void(Collider_Com*, Collider_Com*, float)>>::iterator	StartIter = m_CollisionFunc[CCT_DIONG].begin();
	list<function<void(Collider_Com*, Collider_Com*, float)>>::iterator	EndIter = m_CollisionFunc[CCT_DIONG].end();

	//함수포인터 실행
	for (; StartIter != EndIter; ++StartIter)
		(*StartIter)(this, Dest, DeltaTime);
}

void Collider_Com::OnCollsionEnd(Collider_Com * Dest, float DeltaTime)
{
	list<function<void(Collider_Com*, Collider_Com*, float)>>::iterator	StartIter = m_CollisionFunc[CCT_END].begin();
	list<function<void(Collider_Com*, Collider_Com*, float)>>::iterator	EndIter = m_CollisionFunc[CCT_END].end();

	//함수포인터 실행
	for (; StartIter != EndIter; ++StartIter)
		(*StartIter)(this, Dest, DeltaTime);
}

void Collider_Com::SetCallback(function<void(Collider_Com*, Collider_Com*, float)> const & _function, COLLSION_CALLBACK_TYPE _type)
{
	m_CollisionFunc[_type].push_back(_function);
}

void Collider_Com::SetCollsionCallback(COLLSION_CALLBACK_TYPE eType, void(*pFunc)(Collider_Com *, Collider_Com *, float))
{
	function<void(Collider_Com *, Collider_Com *, float)> newFunc;

	newFunc = bind(pFunc, placeholders::_1, placeholders::_2, placeholders::_3);
	m_CollisionFunc[eType].push_back(newFunc);
}

bool Collider_Com::CollsionRectToRect(const BoxInfo & Src, const BoxInfo & Dest)
{
	if (Src.Min.x > Dest.Max.x)
		return false;

	else if (Src.Max.x < Dest.Min.x)
		return false;

	else if (Src.Min.y > Dest.Max.y)
		return false;

	else if (Src.Max.y < Dest.Min.y)
		return false;

	return true;
}
