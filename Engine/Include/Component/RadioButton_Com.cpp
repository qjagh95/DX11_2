#include "RadioButton_Com.h"
#include "CheckBox_Com.h"
#include "Transform_Com.h"
#include "Renderer_Com.h"
#include "Material_Com.h"
#include "ColliderRect_Com.h"

#include "../GameObject.h"
#include "../KeyInput.h"

#include "../Scene/Scene.h"
#include "../Scene/Layer.h"

JEONG_USING


RadioButton_Com::RadioSet::RadioSet()
	:RadioObject(NULLPTR), CheckCom(NULLPTR)
{
}

RadioButton_Com::RadioSet::~RadioSet()
{
	SAFE_RELEASE(RadioObject);
	SAFE_RELEASE(CheckCom);
}

RadioButton_Com::RadioButton_Com()
{
	m_UIType = UT_RADIOBUTTON;
	SetTag("RadioButton");
	m_PrevIndex = NULLPTR;
}

RadioButton_Com::RadioButton_Com(const RadioButton_Com & CopyData)
	:UIBase_Com(CopyData)
{
	m_RadioMap.clear();

	unordered_map<string, vector<RadioSet*>>::const_iterator StartIter = CopyData.m_RadioMap.begin();
	unordered_map<string, vector<RadioSet*>>::const_iterator EndIter = CopyData.m_RadioMap.end();

	for (; StartIter != EndIter; StartIter++)
	{
		vector<RadioSet*> TempVec;
		for (size_t i = 0; i < StartIter->second.size(); i++)
		{
			RadioSet* newSet = new RadioSet();
			
			GameObject* newObject = StartIter->second[i]->RadioObject;
			CheckBox_Com* newCheck = StartIter->second[i]->CheckCom;

			newSet->CheckCom = newCheck->Clone();
			newSet->RadioObject = newObject->Clone();

			TempVec.push_back(newSet);

			SAFE_RELEASE(newObject);
			SAFE_RELEASE(newCheck);
		}

		m_RadioMap.insert(make_pair(StartIter->first, TempVec));
		TempVec.clear();
	}
}

RadioButton_Com::~RadioButton_Com()
{
	unordered_map<string, vector<RadioSet*>>::iterator StartIter = m_RadioMap.begin();
	unordered_map<string, vector<RadioSet*>>::iterator EndIter = m_RadioMap.end();

	for (; StartIter != EndIter; StartIter++)
	{
		for (size_t i = 0; i < StartIter->second.size(); i++)
		{
			SAFE_DELETE(StartIter->second[i]);
		}
	}
	m_RadioMap.clear();
}

bool RadioButton_Com::Init()
{
	m_Transform->SetWorldScale(16.0f, 16.0f, 0.0f);

	Renderer_Com* RenderComponent = m_Object->AddComponent<Renderer_Com>("RadioBoxRender");
	RenderComponent->SetMesh("TextureRect");
	RenderComponent->SetRenderState(ALPHA_BLEND);
	RenderComponent->SetShader(CHECKBOX_SHADER);
	RenderComponent->CreateRendererCBuffer("CheckBoxCBuffer", sizeof(CheckBoxCBuffer));
	SAFE_RELEASE(RenderComponent);

	Material_Com* MaterialComponent = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	MaterialComponent->SetDiffuseTexture(0, "Radio", TEXT("RadioButton.png"));
	SAFE_RELEASE(MaterialComponent);

	ColliderRect_Com* RectColl = m_Object->AddComponent<ColliderRect_Com>("RadioBody");
	RectColl->SetInfo(Vector3::Zero, Vector3(16.0f, 16.0f, 0.0f));
	RectColl->SetCollisionGroup("UI");
	SAFE_RELEASE(RectColl);

	return true;
}

int RadioButton_Com::Input(float DeltaTime)
{
	return 0;
}

int RadioButton_Com::Update(float DeltaTime)
{
	unordered_map<string, vector<RadioSet*>>::iterator StartIter = m_RadioMap.begin();
	unordered_map<string, vector<RadioSet*>>::iterator EndIter = m_RadioMap.end();

	int GroupCount = 0;
	for (; StartIter != EndIter; GroupCount++,StartIter++)
	{
		for (size_t i = 0; i < StartIter->second.size(); i++)
		{
			if (StartIter->second[i]->CheckCom->GetCheckState() == CBS_TRUE)
			{
				m_PrevIndex[GroupCount] = i;
				StartIter->second[m_PrevIndex[GroupCount]]->CheckCom->SetCheckState(CBS_FALSE);
				break;
			}
		} 
	}

	if (m_PrevIndex[GroupCount] >= 0)
	{
		StartIter->second[m_PrevIndex[GroupCount]]->CheckCom->SetCheckState(CBS_TRUE);
		m_PrevIndex[GroupCount] = -1;
	}

	return 0;
}

int RadioButton_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void RadioButton_Com::Collision(float DeltaTime)
{
}

void RadioButton_Com::CollisionLateUpdate(float DeltaTime)
{
}

void RadioButton_Com::Render(float DeltaTime)
{
}

RadioButton_Com * RadioButton_Com::Clone()
{
	return new RadioButton_Com(*this);
}

void RadioButton_Com::AfterClone()
{
}

void RadioButton_Com::CreateRadioGroup(const string & GroupName, int Interval, int ButtonCount, Vector3 StartPos, RADIO_DIR dir)
{
	vector<RadioSet*> TempVec;
	for (size_t i = 0; i < ButtonCount; i++)
	{
		RadioSet* newSet = new RadioSet();
		GameObject* newObject = GameObject::CreateObject("RadioObject", m_Layer);
		CheckBox_Com* newCheck = newObject->AddComponent<CheckBox_Com>("RadioCom");

		newSet->RadioObject = newObject;
		newSet->CheckCom = newCheck;

		float xPos;
		float yPos;

		switch (dir)
		{
			case RD_DOWN:
			{
				yPos = StartPos.y + (float)Interval * (float)i;
				newSet->RadioObject->GetTransform()->SetWorldPos(StartPos.y, yPos, 0.0f);
			}
				break;
			case RD_RIGHT:
			{
				xPos = StartPos.x + (float)Interval * (float)i;
				newSet->RadioObject->GetTransform()->SetWorldPos(xPos, StartPos.y, 0.0f);
			}
				break;
		}

		TempVec.push_back(newSet);
	}

	m_RadioMap.insert(make_pair(GroupName, TempVec));
}
