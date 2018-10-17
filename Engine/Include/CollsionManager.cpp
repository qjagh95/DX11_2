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
	newGroup->CountX = CountX;					//X�� ���� ũ��
	newGroup->CountY = CountY;					//Y�� ���� ũ��
	newGroup->CountZ = CountZ;					//Z�� ���� ũ��
	newGroup->Count = CountX * CountY * CountZ; //��ü ���� ����
	newGroup->Max = Max;						//���� ��ü�� ũ��
	newGroup->Min = Min;						//�ּҰ� ex(0 0 0 ~ 1280 720 0)
	newGroup->Lenth = Max - Min;				//������ ������
	newGroup->SpaceLenth = newGroup->Lenth / Vector3((float)CountX, (float)CountY, (float)CountZ);
	//���� �ϳ��� ũ��. ������ / ���Ұ���

	//��ü ���ҵ� ���� ������ŭ �����Ҵ�.
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
	//�ö��̴�(�浹ü)������Ʈ�� ���ٸ�
	if (object->CheckComponentType(CT_COLLIDER) == false)
		return;

	Scene* CurScene = SceneManager::Get()->GetCurScene();
	Transform_Com* getTransform = CurScene->GetMainCameraTransform();
	Vector3 CameraPos = getTransform->GetWorldPos();

	SAFE_RELEASE(CurScene);

	//�ö��̴� ������Ʈ ����Ʈ�� �����´� (�浹ü�� ������ �� �� �ֱ⶧����) (��ĳ����)
	const list<Component_Base*>* getComList = object->FindComponentFromType(CT_COLLIDER);

	list<Component_Base*>::const_iterator StartIter = getComList->begin();
	list<Component_Base*>::const_iterator EndIter = getComList->end();

	for (; StartIter != EndIter; StartIter++)
	{
		//�ڽ�������Ʈ�� ����ȯ. ����ó���� ���������ִ� ������ �ε����� ������ �����Ѵ�.
		((Collider_Com*)*StartIter)->ClearSectionIndex();
		//���� �����ִ� �׷��� ã�´�.
		CollsionGroup* getGroup = FindGroup(((Collider_Com*)*StartIter)->GetCollisionGroupName());

		if (getGroup == NULLPTR)
		{
			TrueAssert(true);
			return;
		}

		//���߿� �ʿ��ϸ� ī�޶� �浹���� ��ü�� �ٿ��༭ �浹������ ī�޶��� ��ġ�� 
		//�������� ���� �� �ֵ��� �Ѵ�.
		//if (getGroup->Type == CGT_2D)
		//{
		//	Vector3 cPos = Vector3((float)Device::Get()->GetWinSize().Width, (float)Device::Get()->GetWinSize().Height, 0.0f);
		//	CameraPos += cPos * 0.5f;
		//}

		//if (((Collider_Com*)*StartIter)->GetCollisionGroupName() == "UI")
		//	CameraPos = Vector3::Zero;


		//���� Pos�� ��Ÿ����.
		Vector3	SectionMin = ((Collider_Com*)*StartIter)->GetSectionMin();
		Vector3	SectionMax = ((Collider_Com*)*StartIter)->GetSectionMax();

		int	xMin = 0;
		int xMax = 0;
		int yMin = 0;
		int yMax = 0;
		int zMin = 0;
		int zMax = 0;

		//���� ��ġ�� ���� �����ε����� ���Ѵ�.
		xMin = (int)(SectionMin.x - getGroup->Min.x) / (int)getGroup->SpaceLenth.x;
		xMax = (int)(SectionMax.x - getGroup->Min.x) / (int)getGroup->SpaceLenth.x;
		yMin = (int)(SectionMin.y - getGroup->Min.y) / (int)getGroup->SpaceLenth.y;
		yMax = (int)(SectionMax.y - getGroup->Min.y) / (int)getGroup->SpaceLenth.y;

		//Z�� ������ �ϳ��� �־����. (���ε���� ����)
		if (getGroup->CountZ > 1)
		{
			zMin = (int)(SectionMin.z - getGroup->Min.z) / (int)getGroup->SpaceLenth.z;
			zMax = (int)(SectionMax.z - getGroup->Min.z) / (int)getGroup->SpaceLenth.z;
		}

		vector<int> Index;
		for (int z = zMin; z <= zMax; z++)
		{
			//����ó��
			if (z < 0 || z >= getGroup->CountZ)
				continue;

			for (int y = yMin; y <= yMax; y++)
			{
				//����ó��
				if (y < 0 || y >= getGroup->CountY)
					continue;

				for (int x = xMin; x <= xMax; x++)
				{
					//����ó��
					if (x < 0 || x >= getGroup->CountX)
						continue;

					//�ε��� ����
					int	idx = z * (getGroup->CountX * getGroup->CountY) + y * getGroup->CountX + x;
					//���� ���� ������ �ε����� �־��ش�.
					((Collider_Com*)*StartIter)->AddCollisionSection(idx);
					Index.push_back(idx);

					CollsionSection* getSection = &getGroup->SectionList[idx];
					
					//�迭 ���Ҵ����(����)
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

	//��ü �׷� �� ��ŭ �ݺ�����.
	for (; StartIter != EndIter; StartIter++)
	{
		//��ü ���ҵ� ������ŭ �ݺ�����.
		for (int i = 0; i < StartIter->second->Count; i++)
		{
			CollsionSection* getSection = &StartIter->second->SectionList[i];

			//�浹ü���� 1�����ϸ� ���ʿ䰡����.
			if (getSection->Size < 2)
			{
				for (int j = 0; j < getSection->Size; j++)
					getSection->ColliderList[j]->CheckPrevCollisionInSection(DeltaTime);

				getSection->Size = 0;
				continue;
			}

			for (int j = 0; j < getSection->Size; j++)
				getSection->ColliderList[j]->CheckPrevCollisionInSection(DeltaTime);

			//�� ���� �� �浹ü ����ŭ �ݺ��Ѵ�.
			//�������Ĳ�.
			for (int j = 0; j < getSection->Size - 1; j++)
			{
				for (int k = j + 1; k < getSection->Size; k++)
				{
					GameObject* Src = getSection->ColliderList[j]->GetGameObject();
					GameObject* Dest = getSection->ColliderList[k]->GetGameObject();

					//���� ���� ���� �浹ü�� �浹�Ѵٸ�..? �����ȵ�
					if (Src == Dest)
						continue;

					Collider_Com* CollSrc = getSection->ColliderList[j];
					Collider_Com* CollDest = getSection->ColliderList[k];

					if (CollSrc->Collsion(CollDest, DeltaTime) == true)
					{
						//ó���浹�ɰ��
						if (CollSrc->CheckPrevCollision(CollDest) == false)
						{
							CollSrc->AddPrevCollision(CollDest);
							CollDest->AddPrevCollision(CollSrc);

							CollSrc->OnCollsionFirst(CollDest, DeltaTime);
							CollDest->OnCollsionFirst(CollSrc, DeltaTime);
						}
						//�����浹ü�� �������(�浹���ΰ��)
						else
						{
							CollSrc->OnCollsionDoing(CollDest, DeltaTime);
							CollDest->OnCollsionDoing(CollSrc, DeltaTime);
						}
					}
					//�浹 ���ϰ��ִµ� ���� �浹ü�� �������
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
