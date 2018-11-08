#include "stdafx.h"
#include "Transform_Com.h"
#include "../GameObject.h"

JEONG_USING

Transform_Com::Transform_Com()
{
	m_ComType = CT_TRANSFORM;
	m_isUpdate = true;
	m_isStatic = false;
	m_ParentFlag = 0;
	m_ParentTransform = NULLPTR;
}

Transform_Com::Transform_Com(const Transform_Com& copyObject)
	:Component_Base(copyObject)
{
	*this = copyObject;
	m_ParentTransform = NULLPTR;
	m_isUpdate = true;
}

Transform_Com::~Transform_Com()
{
	Safe_Release_VecList(m_ChildTransList);
}

bool Transform_Com::Init()
{
	for (int i = 0; i < 3; i++)
	{
		m_LocalAxis[i] = Vector3::Axis[i];
		m_WorldAxis[i] = Vector3::Axis[i];
	}

	return true;
}

int Transform_Com::Input(float DeltaTime)
{
	return 0;
}
//���⼱ ������ ������Ʈ�� ��� ������.
//������Ʈ�� ���� Transform�� �������ִ�.
int Transform_Com::Update(float DeltaTime)
{
	if (m_isStatic == true)
		return 0;
	else if (m_isUpdate == false)
		return 0;

	m_MatLocal = m_MatLocalScale * m_MatLocalRotation * m_MatLocalPos;

	if (m_ParentTransform != NULLPTR)
	{
		if ((m_ParentFlag & TPF_POS ) && (m_ParentFlag & TPF_ROT))
			m_MatParent = m_ParentTransform->GetParentMatrixNoScale();
		else if (m_ParentFlag & TPF_POS)
			m_MatParent = m_ParentTransform->GetParentMatrixPos();
		else if (m_ParentFlag & TPF_ROT)
			m_MatParent = m_ParentTransform->GetParentMatrixRot();
		else
			m_MatParent.Identity();
	}

	//World = S R T����.
	m_MatWorld = m_MatWorldScale * m_MatWorldRotation * m_MatWorldPos * m_MatParent;

	m_isUpdate = false;

	return 0;
}

int Transform_Com::LateUpdate(float DeltaTime)
{
	if (m_isStatic == true)
		return 0;
	else if (m_isUpdate == false)
		return 0;

	m_MatLocal = m_MatLocalScale * m_MatLocalRotation * m_MatLocalPos;

	if (m_ParentTransform != NULLPTR)
	{
		if ((m_ParentFlag & TPF_POS) && (m_ParentFlag & TPF_ROT))
			m_MatParent = m_ParentTransform->GetParentMatrixNoScale();
		else if (m_ParentFlag & TPF_POS)
			m_MatParent = m_ParentTransform->GetParentMatrixPos();
		else if (m_ParentFlag & TPF_ROT)
			m_MatParent = m_ParentTransform->GetParentMatrixRot();
		else
			m_MatParent.Identity();
	}

	//World = S R T����.
	m_MatWorld = m_MatWorldScale * m_MatWorldRotation * m_MatWorldPos * m_MatParent;

	m_isUpdate = false;

	return 0;
}

void Transform_Com::Collision(float DeltaTime)
{
}

void Transform_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Transform_Com::Render(float DeltaTime)
{
}

Transform_Com * Transform_Com::Clone()
{
	return new Transform_Com(*this);
}

void Transform_Com::SetLocalScale(const Vector3 & vScale)
{
	//ũ�Ⱚ�� �޴´�
	m_LocalScale = vScale;
	//��Ŀ� ũ�Ⱚ�� ���Ѵ�
	m_MatLocalScale.Scaling(m_LocalScale);

	m_isUpdate = true;
}

void Transform_Com::SetLocalScale(float x, float y, float z)
{
	//ũ�Ⱚ�� �޴´�
	m_LocalScale = Vector3(x, y, z);
	//��Ŀ� ũ�Ⱚ�� ���Ѵ�
	m_MatLocalScale.Scaling(m_LocalScale);

	m_isUpdate = true;
}

void Transform_Com::SetLocalRotation(const Vector3 & vRot)
{
	//ȸ������ �޴´�
	m_LocalRotation = vRot;
	//ȸ����Ŀ� �����ش�
	m_MatLocalRotation.Rotation(m_LocalRotation);

	m_isUpdate = true;

	ComputeLocalAxis();
}

void Transform_Com::SetLocalRotation(float x, float y, float z)
{
	//ȸ������ �޴´�
	m_LocalRotation = Vector3(x, y, z);
	//ȸ����Ŀ� �����ش�
	m_MatLocalRotation.Rotation(m_LocalRotation);

	m_isUpdate = true;

	ComputeLocalAxis();
}

void Transform_Com::SetLocalRotX(float x)
{
	//ȸ������ �޴´�
	m_LocalRotation.x = x;
	//ȸ����Ŀ� �����ش�
	m_MatLocalRotation.Rotation(m_LocalRotation);

	m_isUpdate = true;

	ComputeLocalAxis();
}

void Transform_Com::SetLocalRotY(float y)
{
	//ȸ������ �޴´�
	m_LocalRotation.y = y;
	//ȸ����Ŀ� �����ش�
	m_MatLocalRotation.Rotation(m_LocalRotation);

	m_isUpdate = true;

	ComputeLocalAxis();
}

void Transform_Com::SetLocalRotZ(float z)
{
	//ȸ������ �޴´�
	m_LocalRotation.z = z;
	//ȸ����Ŀ� �����ش�
	m_MatLocalRotation.Rotation(m_LocalRotation);

	m_isUpdate = true;

	ComputeLocalAxis();
}

void Transform_Com::SetLocalPos(const Vector3 & vPos)
{
	m_LocalPos = vPos;

	m_MatLocalPos.Translation(m_LocalPos);

	m_isUpdate = true;
}

void Transform_Com::SetLocalPos(float x, float y, float z)
{
	m_LocalPos = Vector3(x, y, z);

	m_MatLocalPos.Translation(m_LocalPos);

	m_isUpdate = true;
}

//�� ���� ������ �˾ƿ´�.
void Transform_Com::ComputeLocalAxis()
{
	Matrix matRot = m_MatLocalRotation;

	if (m_ParentTransform != NULLPTR)
		matRot *= m_ParentTransform->GetLocalRotMatrix();

	for (int i = 0; i < 3; ++i)
	{
		//��� ���Լ�.
		m_LocalAxis[i] = Vector3::Axis[i].TransformNormal(matRot);
		//ũ��1���ͷ� ���� ���Ⱚ�� ������ ����.
		m_LocalAxis[i].Nomallize();
	}
}

void Transform_Com::SetWorldScale(const Vector3 & vScale)
{
	//ũ�Ⱚ�� �޴´�
	m_WorldScale = vScale;
	ScaleParent();
}

void Transform_Com::SetWorldScale(float x, float y, float z)
{
	//ũ�Ⱚ�� �޴´�
	m_WorldScale = Vector3(x, y, z);
	ScaleParent();
}

void Transform_Com::SetWorldRotX(float x)
{
	//ȸ������ �޴´�
	m_WorldRotation.x = x;
	//ȸ����Ŀ� �����ش�
	m_MatWorldRotation.Rotation(m_WorldRotation);

	m_isUpdate = true;

	ComputeWorldAxis();
	PosParent();
}

void Transform_Com::SetWorldRotY(float y)
{
	//ȸ������ �޴´�
	m_WorldRotation.y = y;
	//ȸ����Ŀ� �����ش�
	m_MatWorldRotation.Rotation(m_WorldRotation);

	m_isUpdate = true;

	ComputeWorldAxis();
	PosParent();
}

void Transform_Com::SetWorldRotZ(float z)
{
	//ȸ������ �޴´�
	m_WorldRotation.z = z;
	//ȸ����Ŀ� �����ش�
	m_MatWorldRotation.Rotation(m_WorldRotation);

	m_isUpdate = true;

	ComputeWorldAxis();
	PosParent();
}

void Transform_Com::SetWorldPos(const Vector3 & vPos)
{
	Vector3 TempPos = vPos - m_WorldPos;	
	m_WorldRelativePos += TempPos;

	m_WorldPos = vPos;

	PosParent();
}

void Transform_Com::SetWorldPos(float x, float y, float z)
{
	Vector3	vPos(x, y, z);
	Vector3	vMove = vPos - m_WorldPos;

	m_WorldRelativePos += vMove;
	m_WorldPos = vPos;

	PosParent();
}
void Transform_Com::SetWorldRelativePos(const Vector3& Pos)
{
	m_WorldRelativePos = Pos;
	PosParent();
}

void Transform_Com::SetWorldRelativePos(float x, float y, float z)
{
	m_WorldRelativePos = Vector3(x, y, z);
	PosParent();
}

void Transform_Com::SetWorldPivot(const Vector3& vPos)
{
	m_Pivot = vPos;
}

void Transform_Com::SetWorldPivot(float x, float y, float z)
{
	m_Pivot = Vector3(x, y, z);
}

void Transform_Com::Move(AXIS eAxis, float Speed)
{
	Move(m_WorldAxis[eAxis] * Speed);
}

void Transform_Com::Move(AXIS eAxis, float Speed, float DeltaTime)
{
	Move(m_WorldAxis[eAxis] * Speed * DeltaTime);
}

void Transform_Com::Move(const Vector3 & vDir, float Speed)
{
	Move(vDir * Speed);
}

void Transform_Com::Move(const Vector3 & vDir, float Speed, float DeltaTime)
{
	Move(vDir * Speed * DeltaTime);
}

void Transform_Com::Move(const Vector3 & vMove)
{
	m_WorldRelativePos += vMove;
	m_WorldPos += vMove;

	PosParent();
}

void Transform_Com::RotationX(float x)
{	
	Rotation(Vector3(x, 0.0f, 0.0f));
}

void Transform_Com::RotationX(float x, float DeltaTime)
{
	Rotation(Vector3(x * DeltaTime, 0.0f, 0.0f));
}

void Transform_Com::RotationY(float y)
{
	Rotation(Vector3(0.0f, y, 0.0f));
}

void Transform_Com::RotationY(float y, float DeltaTime)
{
	Rotation(Vector3(0.0f, y * DeltaTime , 0.0f));
}

void Transform_Com::RotationZ(float z)
{
	Rotation(Vector3(0.0f, 0.0f, z));
}

void Transform_Com::RotationZ(float z, float DeltaTime)
{
	//�����̼��Լ����� += ���ش�.
	Rotation(Vector3(0.0f, 0.0f, z * DeltaTime));
}

void Transform_Com::Rotation(const Vector3 & vRot, float DeltaTime)
{
	Rotation(vRot * DeltaTime);
}

void Transform_Com::Rotation(const Vector3 & vRot)
{
	m_WorldRotation += vRot;
	m_MatWorldRotation.Rotation(m_WorldRotation);
	//ȸ����İ������� �� WorldAxis���� ��ȯ�Ѵ�.
	ComputeWorldAxis();
	m_isUpdate = true;

	PosParent();
	UpdateTransform();
}

//�� ���� ������ �˾ƿ´�.
void Transform_Com::ComputeWorldAxis()
{
	Matrix matRot = m_MatWorldRotation;

	if (m_ParentTransform != NULLPTR)
		matRot *= m_ParentTransform->GetWorldRotMatrix();

	for (int i = 0; i < 3; ++i)
	{
		//������ ��Ʈ����(ȸ�����)�� ���� ���͸� ��ȯ�Ѵ�.
		m_WorldAxis[i] = Vector3::Axis[i].TransformNormal(matRot);
		//ũ��1���ͷ� ���� ���Ⱚ�� ������ ����.
		m_WorldAxis[i].Nomallize();
	}
}

void Transform_Com::LookAt(GameObject * object, AXIS eAxis)
{
	LookAt(object->GetTransform()->GetWorldPos(), eAxis);
}

void Transform_Com::LookAt(Component_Base * component, AXIS eAxis)
{
	LookAt(component->GetTransform()->GetWorldPos(), eAxis);
}

void Transform_Com::LookAt(const Vector3 & Vec, AXIS eAxis)
{
	//�ٶ󺸷��� ������ ���Ѵ�. (���ͻ��� = �ٶ󺸴¹���) 
	Vector3 View = Vec - m_WorldPos;
	View.Nomallize();

	//�������� �����Ѵ�.
	Vector3 Axis = Vector3::Axis[eAxis];

	//������� �ٶ󺸷��� ����(View)�� ������ ���Ѵ� (����)
	float Angle = Axis.GetAngle(View);

	Vector3 vRotAxis = Axis.Cross(View);
	vRotAxis.Nomallize();

	//���� �࿡ ���� ȸ����� ����.
	m_MatWorldRotation.RotationAxis(Angle, vRotAxis);
	ComputeWorldAxis();

	UpdateTransform();
}

float Transform_Com::GetAngle(GameObject * Target)
{
	return GetAngle(Target->GetTransform());
}

float Transform_Com::GetAngle(Transform_Com * Target)
{
	return m_WorldPos.GetAngle(Target->GetWorldPos());
}

void Transform_Com::SetParentFlag(int Flag)
{
	m_ParentFlag = Flag;
}

void Transform_Com::AddParentFlag(TRANSFORM_PARENT_FLAG Flag)
{
	m_ParentFlag |= Flag;
}

void Transform_Com::DeleteParentFlag(TRANSFORM_PARENT_FLAG Flag)
{
	if (m_ParentFlag & Flag)
		m_ParentFlag ^= Flag; //xor0�϶� 1 , 1�϶� 0
}

void Transform_Com::DeleteParentFlag()
{
	m_ParentFlag = 0;
}

void Transform_Com::ScaleParent()
{
	if (m_ParentTransform == NULLPTR)
		m_WorldRelativeScale = m_WorldScale;
	else if (!(m_ParentFlag & TPF_SCALE))
		m_WorldRelativeScale = m_WorldScale;
	else
		m_WorldRelativeScale = m_WorldScale / m_ParentTransform->m_WorldScale;  //������ ���Ѵ�. �θ� 100 �ڽ� 50 = 0.5

	m_MatWorldScale.Scaling(m_WorldRelativeScale);

	m_isUpdate = true;

	if (m_ChildTransList.empty() == true)
		return;

	list<Transform_Com*>::iterator StartIter = m_ChildTransList.begin();
	list<Transform_Com*>::iterator EndIter = m_ChildTransList.end();

	for (; StartIter != EndIter; StartIter++)
		(*StartIter)->ScaleParent();
}

void Transform_Com::PosParent()
{
	if (m_ParentTransform == NULLPTR)
		m_WorldRelativePos = m_WorldPos;
	else if (!(m_ParentFlag & TPF_POS))
		m_WorldRelativePos = m_WorldPos;

	m_MatWorldPos.Translation(m_WorldRelativePos);

	if (m_ParentTransform != NULLPTR)
	{
		Matrix matParent;
		
		if ((m_ParentFlag & TPF_POS) && (m_ParentFlag & TPF_ROT))
			matParent = m_ParentTransform->GetParentMatrixNoScale();
		else if (m_ParentFlag & TPF_POS)
			matParent = m_ParentTransform->GetParentMatrixPos();
		else if (m_ParentFlag & TPF_ROT)
			matParent = m_ParentTransform->GetParentMatrixRot();
		else
			matParent.Identity();

		m_WorldPos = m_WorldRelativePos.TransformCoord(matParent);
	}

	m_isUpdate = true;

	if (m_ChildTransList.empty() == true)
		return;

	list<Transform_Com*>::iterator StartIter = m_ChildTransList.begin();
	list<Transform_Com*>::iterator EndIter = m_ChildTransList.end();

	for (; StartIter != EndIter ; StartIter++)
		(*StartIter)->PosParent();
}

Matrix Transform_Com::GetParentMatrixNoScale() const
{
	if (m_ParentTransform == NULLPTR)
		return m_MatWorldRotation * m_MatWorldPos;

	//��������� ��� Ÿ�� ��.
	return m_MatWorldRotation * m_MatWorldPos * m_ParentTransform->GetParentMatrixNoScale();
}

Matrix Transform_Com::GetParentMatrixRot() const
{
	if (m_ParentTransform == NULLPTR)
		return m_MatWorldRotation;

	return m_MatWorldRotation * m_ParentTransform->GetParentMatrixRot();
}

Matrix Transform_Com::GetParentMatrixPos() const	
{
	if (m_ParentTransform == NULLPTR)
		return m_MatWorldPos;

	return m_MatWorldPos * m_ParentTransform->GetParentMatrixPos();
}

void Transform_Com::UpdateTransform()
{
	m_isUpdate = true;

	if (m_ChildTransList.empty() == false)
		return;

	list<Transform_Com*>::iterator	StartIter = m_ChildTransList.begin();
	list<Transform_Com*>::iterator	EndIter = m_ChildTransList.end();

	for (; StartIter != EndIter; ++StartIter)
		(*StartIter)->UpdateTransform();
}