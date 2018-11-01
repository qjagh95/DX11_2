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

RadioButton_Com::RadioButton_Com()
{
	m_UIType = UT_RADIOBUTTON;
	SetTag("RadioButton");

	m_CheckState = CBS_FALSE;
	m_CheckBoxCBuffer = { 0 };
}

RadioButton_Com::RadioButton_Com(const RadioButton_Com & CopyData)
	:CheckBox_Com(CopyData)
{
}

RadioButton_Com::~RadioButton_Com()
{
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
	RectColl->SetCallback([this](Collider_Com* _src, Collider_Com* _dest, float _time) { MouseHit(_src, _dest, _time);}, CCT_DOING);
	RectColl->SetCallback([this](Collider_Com* _src, Collider_Com* _dest, float _time) { MouseOut(_src, _dest, _time);}, CCT_END);

	SAFE_RELEASE(RectColl);

	m_CheckBoxCBuffer.CheckBoxColor = Vector4::White;
	m_CheckBoxCBuffer.isCheck = false;

	return true;
}

int RadioButton_Com::Input(float DeltaTime)
{
	CheckBox_Com::Input(DeltaTime);
	return 0;
}

int RadioButton_Com::Update(float DeltaTime)
{
	CheckBox_Com::Update(DeltaTime);

	return 0;
}

int RadioButton_Com::LateUpdate(float DeltaTime)
{
	CheckBox_Com::LateUpdate(DeltaTime);

	return 0;
}

void RadioButton_Com::Collision(float DeltaTime)
{
	CheckBox_Com::Collision(DeltaTime);
}

void RadioButton_Com::CollisionLateUpdate(float DeltaTime)
{
	CheckBox_Com::CollisionLateUpdate(DeltaTime);
}

void RadioButton_Com::Render(float DeltaTime)
{
	CheckBox_Com::Render(DeltaTime);
}

RadioButton_Com * RadioButton_Com::Clone()
{
	return new RadioButton_Com(*this);
}

void RadioButton_Com::AfterClone()
{
}