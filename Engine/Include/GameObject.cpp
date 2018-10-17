#include "GameObject.h"
#include "CollsionManager.h"

#include "Scene/Layer.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"

#include "Component/Transform_Com.h"
#include "Component/Renderer_Com.h"

JEONG_USING

unordered_map<Scene*, unordered_map<string, GameObject*>> GameObject::m_ProtoTypeMap;

GameObject::GameObject()
	:m_Scene(NULLPTR), m_Layer(NULLPTR), m_Transform(NULLPTR), m_MoveDir(MD_UP)
{
	SetTag("GameObject");
}

GameObject::GameObject(const GameObject& copyObject)
{
	*this = copyObject;

	m_Transform = copyObject.m_Transform->Clone();
	m_Transform->m_Transform = m_Transform;

	m_ComponentList.clear();
	m_FindComList.clear();

	list<Component_Base*>::const_iterator StartIter = copyObject.m_ComponentList.begin();
	list<Component_Base*>::const_iterator EndIter = copyObject.m_ComponentList.end();

	for (; StartIter != EndIter ; StartIter++)
	{
		Component_Base* newComponent = (*StartIter)->Clone();
		newComponent->m_Object = this;
		newComponent->m_Transform = m_Transform;

		m_ComponentList.push_back(newComponent);
	}

	Renderer_Com* getRender = FindComponentFromType<Renderer_Com>(CT_RENDER);

	if(getRender != NULLPTR)
	{
		getRender->CheckComponent();
		SAFE_RELEASE(getRender);
	}
}

GameObject::~GameObject()
{
	SAFE_RELEASE(m_Transform);
	Safe_Release_VecList(m_FindComList);
	Safe_Release_VecList(m_ComponentList);
}

bool GameObject::Init()
{
	m_Transform = new Transform_Com();
	m_Transform->Init();

	m_Transform->m_Transform = m_Transform;

	return true;
}

int GameObject::Input(float DeltaTime)
{
	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetIsActive() == false)
		{
			Renderer_Com* pRenderer = FindComponentFromType<Renderer_Com>(CT_RENDER);
			if (pRenderer != NULLPTR)
			{
				pRenderer->DeleteComponentCBuffer(*StartIter);
				SAFE_RELEASE(pRenderer);
			}

			SAFE_RELEASE((*StartIter));
			StartIter = m_ComponentList.erase(StartIter);
			continue;
		}
		else if ((*StartIter)->GetIsShow() == false)
		{
			StartIter++;
			continue;
		}
		(*StartIter)->Input(DeltaTime);
		StartIter++;
	}

	return 0;
}

int GameObject::Update(float DeltaTime)
{
	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetIsActive() == false)
		{
			Renderer_Com* pRenderer = FindComponentFromType<Renderer_Com>(CT_RENDER);
			if (pRenderer != NULLPTR)
			{
				pRenderer->DeleteComponentCBuffer(*StartIter);
				SAFE_RELEASE(pRenderer);
			}

			SAFE_RELEASE((*StartIter));
			StartIter = m_ComponentList.erase(StartIter);
			continue;
		}
		else if ((*StartIter)->GetIsShow() == false)
		{
			StartIter++;
			continue;
		}
		(*StartIter)->Update(DeltaTime);
		StartIter++;
	}

	m_Transform->Update(DeltaTime);

	return 0;
}

int GameObject::LateUpdate(float DeltaTime)
{
	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetIsActive() == false)
		{
			Renderer_Com* pRenderer = FindComponentFromType<Renderer_Com>(CT_RENDER);
			if (pRenderer != NULLPTR)
			{
				pRenderer->DeleteComponentCBuffer(*StartIter);
				SAFE_RELEASE(pRenderer);
			}

			SAFE_RELEASE((*StartIter));
			StartIter = m_ComponentList.erase(StartIter);
			continue;
		}
		else if ((*StartIter)->GetIsShow() == false)
		{
			StartIter++;
			continue;
		}
		(*StartIter)->LateUpdate(DeltaTime);
		StartIter++;
	}
	m_Transform->LateUpdate(DeltaTime);

	return 0;
}

void GameObject::Collision(float DeltaTime)
{
	CollsionManager::Get()->AddCollsion(this);

	//list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	//list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	//for (; StartIter != EndIter;)
	//{
	//	if ((*StartIter)->GetIsActive() == false)
	//	{
	//		Renderer_Com* pRenderer = FindComponentFromType<Renderer_Com>(CT_RENDER);
	//		if (pRenderer != NULLPTR)
	//		{
	//			pRenderer->DeleteComponentCBuffer(*StartIter);
	//			SAFE_RELEASE(pRenderer);
	//		}

	//		SAFE_RELEASE((*StartIter));
	//		StartIter = m_ComponentList.erase(StartIter);
	//		continue;
	//	}
	//	else if ((*StartIter)->GetIsShow() == false)
	//	{
	//		StartIter++;
	//		continue;
	//	}
	//	(*StartIter)->Collision(DeltaTime);
	//	StartIter++;
	//}

	//m_Transform->Collision(DeltaTime);
}

void GameObject::CollisionLateUpdate(float DeltaTime)
{
	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (; StartIter != EndIter;)
	{
		Renderer_Com* pRenderer = FindComponentFromType<Renderer_Com>(CT_RENDER);
		if (pRenderer != NULLPTR)
		{
			pRenderer->DeleteComponentCBuffer(*StartIter);
			SAFE_RELEASE(pRenderer);
		}

		if ((*StartIter)->GetIsActive() == false)
		{
			SAFE_RELEASE((*StartIter));
			StartIter = m_ComponentList.erase(StartIter);
			continue;
		}
		else if ((*StartIter)->GetIsShow() == false)
		{
			StartIter++;
			continue;
		}
		(*StartIter)->CollisionLateUpdate(DeltaTime);
		StartIter++;
	}

}

void GameObject::Render(float DeltaTime)
{
	m_Transform->Render(DeltaTime);

	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetIsActive() == false)
		{
			Renderer_Com* pRenderer = FindComponentFromType<Renderer_Com>(CT_RENDER);
			if (pRenderer != NULLPTR)
			{
				pRenderer->DeleteComponentCBuffer(*StartIter);
				SAFE_RELEASE(pRenderer);
			}

			SAFE_RELEASE((*StartIter));
			StartIter = m_ComponentList.erase(StartIter);
			continue;
		}
		else if ((*StartIter)->GetIsShow() == false)
		{
			StartIter++;
			continue;
		}
		(*StartIter)->Render(DeltaTime);
		StartIter++;
	}
}

GameObject * GameObject::Clone()
{
	return new GameObject(*this);
}

void GameObject::SetScene(Scene * scene)
{
	m_Scene = scene;
	m_Transform->m_Scene = scene;

	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (;StartIter != EndIter; StartIter++)
		(*StartIter)->m_Scene = scene;
}

void GameObject::SetLayer(Layer * layer)
{
	m_Layer = layer;
	m_Transform->m_Layer = layer;

	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (;StartIter != EndIter; StartIter++)
		(*StartIter)->m_Layer = layer;
}

GameObject * GameObject::CreateObject(const string & TagName, Layer * layer)
{
	GameObject*	newObject = new GameObject();
	newObject->SetTag(TagName);

	if (newObject->Init() == false)
	{
		SAFE_RELEASE(newObject);
		return NULLPTR;
	}

	//해당 레이어에 오브젝트 추가를 해준다.
	if (layer != NULLPTR)
		layer->AddObject(newObject);

	return newObject;
}

const list<Component_Base*>* GameObject::GetComponentList() const
{
	return &m_ComponentList;
}

bool GameObject::CheckComponentType(COMPONENT_TYPE eType)
{
	list<Component_Base*>::const_iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::const_iterator EndIter = m_ComponentList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		if ((*StartIter)->GetComType() == eType)
			return true;
	}
	return false;
}

Component_Base * GameObject::AddComponent(Component_Base * component)
{
	component->m_Scene = m_Scene;
	component->m_Layer = m_Layer;
	component->m_Transform = m_Transform;
	component->m_Object = this;
	component->AddRefCount();

	m_ComponentList.push_back(component);

	Renderer_Com* pRender = FindComponentFromType<Renderer_Com>(CT_RENDER);

	if (pRender != NULLPTR)
	{
		pRender->CheckComponent();
		SAFE_RELEASE(pRender);
	}

	return component;
}

GameObject * GameObject::CreateProtoType(const string & TagName, bool isCurrent)
{
	Scene* getScene = NULLPTR;

	if (isCurrent == true)
		getScene = SceneManager::Get()->GetCurScene();
	else
		getScene = SceneManager::Get()->GetNextScene();

	GameObject* newProtoType = FindProtoType(getScene, TagName);
	
	if (newProtoType != NULLPTR)
		return NULLPTR;

	unordered_map<Scene*, unordered_map<string, GameObject*>>::iterator FindIter = m_ProtoTypeMap.find(getScene);
	unordered_map<string, GameObject*>* pMap = NULLPTR;

	if (FindIter == m_ProtoTypeMap.end())
	{
		unordered_map<string, GameObject*> TempMap;

		m_ProtoTypeMap.insert(make_pair(getScene, TempMap));

		FindIter = m_ProtoTypeMap.find(getScene);
	}

	pMap = &FindIter->second;
	SAFE_RELEASE(getScene);

	newProtoType = new GameObject();
	newProtoType->SetTag(TagName);

	if (newProtoType->Init() == false)
	{
		SAFE_RELEASE(newProtoType);
		return NULLPTR;
	}

	newProtoType->AddRefCount();
	//pMap이 FindIter->Second의 주소를 가지고있으니 FindIter->second에 newProtoType이 들어감
	pMap->insert(make_pair(TagName, newProtoType));

	return newProtoType;
}

GameObject * GameObject::CreateClone(const string & TagName, const string & ProtoTypeTagName, Layer * layer, bool isCurrent)
{
	Scene* getScene = NULLPTR;

	if (isCurrent == true)
		getScene = SceneManager::Get()->GetCurScene();
	else
		getScene = SceneManager::Get()->GetNextScene();

	GameObject* newCloneObject = FindProtoType(getScene, ProtoTypeTagName);
	SAFE_RELEASE(getScene);

	if (newCloneObject == NULLPTR)
		return NULLPTR;

	GameObject*	pClone = newCloneObject->Clone();
	pClone->SetTag(TagName);

	if (layer != NULLPTR)
		layer->AddObject(pClone);

	return pClone;
}

void GameObject::DestroyProtoType(Scene * scene)
{
	unordered_map<Scene*, unordered_map<string, GameObject*>>::iterator FindIter = m_ProtoTypeMap.find(scene);

	if (FindIter == m_ProtoTypeMap.end())
		return;

	Safe_Release_Map(FindIter->second);

	m_ProtoTypeMap.erase(FindIter);
}

void GameObject::DestroyProtoType(Scene * scene, const string & TagName)
{
	unordered_map<Scene*, unordered_map<string, GameObject*>>::iterator FindIter = m_ProtoTypeMap.find(scene);

	if (FindIter == m_ProtoTypeMap.end())
		return;

	unordered_map<string, GameObject*>::iterator FindIter2 = FindIter->second.find(TagName);

	if (FindIter2 == FindIter->second.end())
		return;

	SAFE_RELEASE(FindIter2->second);
	
	FindIter->second.erase(FindIter2);
}

void GameObject::DestroyProtoType()
{
	unordered_map<Scene*, unordered_map<string, GameObject*>>::iterator StartIter = m_ProtoTypeMap.begin();
	unordered_map<Scene*, unordered_map<string, GameObject*>>::iterator EndIter = m_ProtoTypeMap.end();

	for (; StartIter != EndIter; StartIter++)
	{
		Safe_Release_Map(StartIter->second);
	}

	m_ProtoTypeMap.clear();
}

GameObject * GameObject::FindProtoType(Scene * scene, const string & TagName)
{
	unordered_map<Scene*, unordered_map<string, GameObject*>>::iterator FindIter = m_ProtoTypeMap.find(scene);
	
	if (FindIter == m_ProtoTypeMap.end())
		return NULLPTR;

	unordered_map<string, GameObject*>::iterator FindIter2 = FindIter->second.find(TagName);

	if (FindIter2 == FindIter->second.end())
		return NULLPTR;

	return FindIter2->second;
}

GameObject * GameObject::FindObject(const string & TagName)
{
	return SceneManager::Get()->FindObject(TagName);
}

const list<Component_Base*>* GameObject::FindComponentFromTag(const string& TagName)
{
	Safe_Release_VecList(m_FindComList);
	m_FindComList.clear();

	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (; StartIter != EndIter ; StartIter++)
	{
		if ((*StartIter)->GetTag() == TagName)
		{
			(*StartIter)->AddRefCount();
			m_FindComList.push_back(*StartIter);
		}
	}

	return &m_FindComList;
}

const list<Component_Base*>*  GameObject::FindComponentFromType(COMPONENT_TYPE type)
{
	Safe_Release_VecList(m_FindComList);
	m_FindComList.clear();

	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		if ((*StartIter)->GetComType() == type)
		{
			(*StartIter)->AddRefCount();
			m_FindComList.push_back(*StartIter);
		}
	}
	return &m_FindComList;
}

void GameObject::SetTransform(Transform_Com* transform)
{
	m_Transform = transform;
}
void GameObject::SetRotation(const Vector3& vecRot)
{
	m_Transform->Rotation(vecRot);	
}

void GameObject::SetRotationX(float RotX)
{
	m_Transform->SetWorldRotX(RotX);
}

void GameObject::SetRotationY(float RotY)
{
	m_Transform->SetWorldRotY(RotY);
}

void GameObject::SetRotationZ(float RotZ)
{
	m_Transform->SetWorldRotZ(RotZ);
}
