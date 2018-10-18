#include "CollsionManager.h"
#include "GameObject.h"
#include "Device.h"

#include "Scene/Scene.h"
#include "Scene/SceneManager.h"

#include "Component/Transform_Com.h"



JEONG_USING
SINGLETON_VAR_INIT(CollsionManager)

CollsionManager::CollsionManager()
{
}

CollsionManager::~CollsionManager()
{
	Safe_Delete_Map(m_GroupMap);
}

bool CollsionManager::Init()
{
	CreateGroup("Default", Vector3(0.0f, 0.0f, 0.0f), Vector3(5000.f, 5000.f, 0.f), 10, 10, 1, CGT_2D);
	CreateGroup("UI", Vector3(0.0f, 0.0f, 0.0f), Vector3((float)Device::Get()->GetWinSize().Width, (float)Device::Get()->GetWinSize().Width, 0.0f), 4, 4, 1, CGT_2D);

	return true;
}

bool CollsionManager::CreateGroup(const string & KeyName, const Vector3 & Min, const Vector3 & Max, int CountX, int CountY, int CountZ, COLLSION_GROUP_TYPE eType)
{
	CollsionGroup* newGroup = FindGroup(KeyName);

	if (newGroup != NULLPTR)
		return false;   

	newGroup = new CollsionGroup();
	newGroup->Type = eType;						//2D or 3D
	newGroup->CountX = CountX;					//X축 분할 크기
	newGroup->CountY = CountY;					//Y축 분할 크기
	newGroup->CountZ = CountZ;					//Z축 분할 크기
	newGroup->Count = CountX * CountY * CountZ; //전체 분할 갯수
	newGroup->Max = Max;						//공간 전체의 크기
	newGroup->Min = Min;						//최소값 ex(0 0 0 ~ 1280 720 0)
	newGroup->Lenth = Max - Min;				//공간의 사이즈
	newGroup->SpaceLenth = newGroup->Lenth / Vector3((float)CountX, (float)CountY, (float)CountZ);
	//공간 하나당 크기. 사이즈 / 분할갯수

	//전체 분할된 공간 갯수만큼 동적할당.
	newGroup->SectionList = new CollsionSection[newGroup->Count];

	m_GroupMap.insert(make_pair(KeyName, newGroup));

	return true;
}

void CollsionManager::ChangeGroupType(const string& KeyName, COLLSION_GROUP_TYPE eType)
{
	CollsionGroup* getGroup = FindGroup(KeyName);

	if (getGroup == NULLPTR)
		return;

	getGroup->Type = eType;
}

void CollsionManager::AddCollsion(GameObject * object)
{
	//컬라이더(충돌체)컴포넌트가 없다면
	if (object->CheckComponentType(CT_COLLIDER) == false)
		return;

	Scene* CurScene = SceneManager::Get()->GetCurScene();
	Transform_Com* getTransform = CurScene->GetMainCameraTransform();
	Vector3 CameraPos = getTransform->GetWorldPos();

	SAFE_RELEASE(CurScene);

	//컬라이더 컴포넌트 리스트를 가져온다 (충돌체가 여러개 일 수 있기때문에) (업캐스팅)
	const list<Component_Base*>* getComList = object->FindComponentFromType(CT_COLLIDER);

	list<Component_Base*>::const_iterator StartIter = getComList->begin();
	list<Component_Base*>::const_iterator EndIter = getComList->end();

	for (; StartIter != EndIter; StartIter++)
	{
		//자식컴포넌트로 형변환. 예외처리로 내가속해있는 공간의 인덱스를 날리고 시작한다.
		((Collider_Com*)*StartIter)->ClearSectionIndex();
		//내가 속해있는 그룹을 찾는다.
		CollsionGroup* getGroup = FindGroup(((Collider_Com*)*StartIter)->GetCollisionGroupName());

		if (getGroup == NULLPTR)
		{
			TrueAssert(true);
			return;
		}

		//나중에 필요하면 카메라에 충돌영역 자체를 붙여줘서 충돌영역이 카메라의 위치를 
		//기준으로 잡힐 수 있도록 한다.
		//if (getGroup->Type == CGT_2D)
		//{
		//	Vector3 cPos = Vector3((float)Device::Get()->GetWinSize().Width, (float)Device::Get()->GetWinSize().Height, 0.0f);
		//	CameraPos += cPos * 0.5f;
		//}

		//if (((Collider_Com*)*StartIter)->GetCollisionGroupName() == "UI")
		//	CameraPos = Vector3::Zero;


		//나의 Pos를 나타낸다.
		Vector3	SectionMin = ((Collider_Com*)*StartIter)->GetSectionMin();
		Vector3	SectionMax = ((Collider_Com*)*StartIter)->GetSectionMax();

		int	xMin = 0;
		int xMax = 0;
		int yMin = 0;
		int yMax = 0;
		int zMin = 0;
		int zMax = 0;

		//나의 위치에 따른 공간인덱스를 구한다.
		xMin = (int)(SectionMin.x - getGroup->Min.x) / (int)getGroup->SpaceLenth.x;
		xMax = (int)(SectionMax.x - getGroup->Min.x) / (int)getGroup->SpaceLenth.x;
		yMin = (int)(SectionMin.y - getGroup->Min.y) / (int)getGroup->SpaceLenth.y;
		yMax = (int)(SectionMax.y - getGroup->Min.y) / (int)getGroup->SpaceLenth.y;

		//Z는 무조건 하나는 있어야함. (제로디비전 방지)
		if (getGroup->CountZ > 1)
		{
			zMin = (int)(SectionMin.z - getGroup->Min.z) / (int)getGroup->SpaceLenth.z;
			zMax = (int)(SectionMax.z - getGroup->Min.z) / (int)getGroup->SpaceLenth.z;
		}

		vector<int> Index;
		for (int z = zMin; z <= zMax; z++)
		{
			//예외처리
			if (z < 0 || z >= getGroup->CountZ)
				continue;

			for (int y = yMin; y <= yMax; y++)
			{
				//예외처리
				if (y < 0 || y >= getGroup->CountY)
					continue;

				for (int x = xMin; x <= xMax; x++)
				{
					//예외처리
					if (x < 0 || x >= getGroup->CountX)
						continue;

					//인덱스 공식
					int	idx = z * (getGroup->CountX * getGroup->CountY) + y * getGroup->CountX + x;
					//내가 속한 공간의 인덱스를 넣어준다.
					((Collider_Com*)*StartIter)->AddCollisionSection(idx);
					Index.push_back(idx);

					CollsionSection* getSection = &getGroup->SectionList[idx];
					
					//배열 재할당과정(벡터)
					if (getSection->Capacity == getSection->Size)
					{
						getSection->Capacity *= 2;

						Collider_Com** Temp = new Collider_Com*[getSection->Capacity];

						memcpy(Temp, getSection->ColliderList, sizeof(Collider_Com*) * getSection->Size);

						SAFE_DELETE_ARRARY(getSection->ColliderList);

						getSection->ColliderList = Temp;
					}
					getSection->ColliderList[getSection->Size] = (Collider_Com*)*StartIter;
					getSection->Size++;
				}//for(x)
			}//for(y)	
		}//for(z)
	}//for(ColliderList)
}

void CollsionManager::Collsion(float DeltaTime)
{
	unordered_map<string, CollsionGroup*>::iterator StartIter = m_GroupMap.begin();
	unordered_map<string, CollsionGroup*>::iterator EndIter = m_GroupMap.end();

	//전체 그룹 수 만큼 반복돈다.
	for (; StartIter != EndIter; StartIter++)
	{
		//전체 분할된 공간만큼 반복돈다.
		for (int i = 0; i < StartIter->second->Count; i++)
		{
			CollsionSection* getSection = &StartIter->second->SectionList[i];

			//충돌체수가 1개이하면 돌필요가없다.
			if (getSection->Size < 2)
			{
				//공간이 틀어지면 빼줘야한다.
				//4개의 객체와 충돌중인 플레이어가 이동 후 다른 공간인덱스로 옮겨갔는데
				//4개의 객체는 충돌되서 사라지고 플레이어객체는 공간이 틀어졌으니 이전컬라이더를 검사해서
				//있다면 충돌됬단뜻이니 End함수를 한번 호출해야한다.
				for (int j = 0; j < getSection->Size; j++)
					getSection->ColliderList[j]->CheckPrevCollisionInSection(DeltaTime);

				getSection->Size = 0;
				continue;
			}

			for (int j = 0; j < getSection->Size; j++)
				getSection->ColliderList[j]->CheckPrevCollisionInSection(DeltaTime);

			//각 영역 별 충돌체 수만큼 반복한다.
			//버블정렬꼴.
			for (int j = 0; j < getSection->Size - 1; j++)
			{
				for (int k = j + 1; k < getSection->Size; k++)
				{
					GameObject* Src = getSection->ColliderList[j]->GetGameObject();
					GameObject* Dest = getSection->ColliderList[k]->GetGameObject();

					//만약 나와 나의 충돌체가 충돌한다면..? 말도안됨
					if (Src == Dest)
						continue;

					Collider_Com* CollSrc = getSection->ColliderList[j];
					Collider_Com* CollDest = getSection->ColliderList[k];

					if (CollSrc->Collsion(CollDest, DeltaTime) == true)
					{
						//처음충돌될경우
						if (CollSrc->CheckPrevCollision(CollDest) == false)
						{
							CollSrc->AddPrevCollision(CollDest);
							CollDest->AddPrevCollision(CollSrc);

							CollSrc->OnCollsionFirst(CollDest, DeltaTime);
							CollDest->OnCollsionFirst(CollSrc, DeltaTime);
						}
						//이전충돌체가 있을경우(충돌중인경우)
						else
						{
							CollSrc->OnCollsionDoing(CollDest, DeltaTime);
							CollDest->OnCollsionDoing(CollSrc, DeltaTime);
						}
					}
					//충돌 안하고있는데 이전 충돌체가 있을경우
					else
					{
						if (CollSrc->CheckPrevCollision(CollDest) == true)
						{
							CollSrc->OnCollsionEnd(CollDest, DeltaTime);
							CollDest->OnCollsionEnd(CollSrc, DeltaTime);

							CollSrc->ErasePrevCollision(CollDest);
							CollDest->ErasePrevCollision(CollSrc);
						}
					}
				}//for(k)
			}//for(j)
			getSection->Size = 0;
		}//for(SectionCount)
	}//for(GroupCount)
}

CollsionManager::CollsionGroup * CollsionManager::FindGroup(const string & KeyName)
{
	unordered_map<string, CollsionGroup*>::iterator FindIter = m_GroupMap.find(KeyName);

	if (FindIter == m_GroupMap.end())
		return NULLPTR;

	return FindIter->second;
}
