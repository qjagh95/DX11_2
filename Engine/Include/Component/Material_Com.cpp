#include "stdafx.h"
#include "Material_Com.h"
#include "Animation2D_Com.h"

#include "../GameObject.h"

#include "../Resource/ResourceManager.h"
#include "../Resource/Sampler.h"
#include "../Resource/Texture.h"

#include "../Render/ShaderManager.h"

JEONG::Material_Com::Material_Com()
{
	m_ComType = CT_MATERIAL;
}

JEONG::Material_Com::Material_Com(const Material_Com& copyData)
	:Component_Base(copyData)
{
	*this = copyData;

	//m_vecMaterial.clear();

	//for (size_t i = 0; i < copyData.m_vecMaterial.size(); i++)
	//{
	//	vector<JEONG::SubsetMaterial*> TempVec;
	//	m_vecMaterial.push_back(TempVec);

	//	for (size_t j = 0; j < copyData.m_vecMaterial[i].size(); j++)
	//	{
	//		JEONG::SubsetMaterial* newMaterial = new JEONG::SubsetMaterial();
	//		newMaterial->MatrialInfo = copyData.m_vecMaterial[i][j]->MatrialInfo;

	//		for (size_t i = 0; i < length; i++)
	//		{
	//			newMaterial->DiffuseTexture = copyData.m_vecMaterial[i][j]->DiffuseTexture;

	//			if (newMaterial->DiffuseTexture != NULLPTR)
	//				newMaterial->DiffuseTexture->AddRefCount();
	//		}
	//		for (size_t i = 0; i < length; i++)
	//		{

	//		}

	//		newMaterial->DiffuseSampler = copyData.m_vecMaterial[i][j]->DiffuseSampler;

	//		if (newMaterial->DiffuseTexture != NULLPTR)
	//			newMaterial->DiffuseTexture->AddRefCount();

	//		if (newMaterial->DiffuseSampler != NULLPTR)
	//			newMaterial->DiffuseSampler->AddRefCount();

	//		m_vecMaterial[i].push_back(newMaterial);
	//	}
	//}
}

JEONG::Material_Com::~Material_Com()
{
	for (size_t i = 0; i < m_vecMaterial.size(); ++i)
	{
		for (size_t j = 0; j < m_vecMaterial[i].size(); ++j)
		{
			Safe_Release_VecList(m_vecMaterial[i][j]->vecDiffuseSampler);
			Safe_Release_VecList(m_vecMaterial[i][j]->vecDiffuseTexture);
			SAFE_DELETE(m_vecMaterial[i][j]);
		}
		m_vecMaterial[i].clear();
	}
	m_vecMaterial.clear();
}

bool JEONG::Material_Com::Init()
{
	SetMaterial(Vector4::White);

	return true;
}

int JEONG::Material_Com::Input(float DeltaTime)
{
	return 0;
}

int JEONG::Material_Com::Update(float DeltaTime)
{
	return 0;
}

int JEONG::Material_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void JEONG::Material_Com::Collision(float DeltaTime)
{
}

void JEONG::Material_Com::CollisionLateUpdate(float DeltaTime)
{
}

void JEONG::Material_Com::Render(float DeltaTime)
{
}

JEONG::Material_Com * JEONG::Material_Com::Clone()
{
	return new Material_Com(*this);
}

void JEONG::Material_Com::SetMaterial(const Vector4 & Diffuse, int Container, int Subset)
{
	//�����̳ʰ� ���ٸ� �ϳ� �߰��Ѵ�.
	if (Container >= m_vecMaterial.size())
	{
		vector<JEONG::SubsetMaterial*> newVec;
		m_vecMaterial.push_back(newVec);
	}
	//������� ���ٸ� �߰��Ѵ�.
	if (Subset >= m_vecMaterial[Container].size())
		m_vecMaterial[Container].push_back(CreateSubSet());

	//������������
	m_vecMaterial[Container][Subset]->MatrialInfo.Diffuse = Diffuse;
}

void JEONG::Material_Com::SetDiffuseTexture(int RegisterNumber, const string & KeyName, int Container, int Subset)
{
	//�����̳ʰ� ���ٸ� �ϳ� �߰��Ѵ�.
	if (Container >= m_vecMaterial.size())
	{
		vector<JEONG::SubsetMaterial*> newVec;
		m_vecMaterial.push_back(newVec);
	}
	//������� ���ٸ� �߰��Ѵ�.
	if (Subset >= m_vecMaterial[Container].size())
		m_vecMaterial[Container].push_back(CreateSubSet());

	//�ؽ��� �����غ�
	JEONG::SubsetMaterial* getMaterial = m_vecMaterial[Container][Subset];

	if (getMaterial->vecDiffuseTexture.capacity() <= RegisterNumber)
		getMaterial->vecDiffuseTexture.resize(RegisterNumber + 1);

	getMaterial->vecDiffuseTexture[RegisterNumber] = ResourceManager::Get()->FindTexture(KeyName);
}

void JEONG::Material_Com::SetDiffuseTexture(int RegisterNumber, const string & KeyName, const TCHAR * FileName, const string & PathKey, int Container, int Subset)
{
	if (Container >= m_vecMaterial.size())
	{
		vector<JEONG::SubsetMaterial*>	newVec;
		m_vecMaterial.push_back(newVec);
	}

	if (Subset >= m_vecMaterial[Container].size())
		m_vecMaterial[Container].push_back(CreateSubSet());

	JEONG::SubsetMaterial*	getMaterial = m_vecMaterial[Container][Subset];
	//SAFE_RELEASE(getMaterial->DiffuseTexture);

	//�ؽ��İ� ���ٸ� �ʿ� �߰��� ��
	//������ ����.
	ResourceManager::Get()->CreateTexture(KeyName, FileName, PathKey);

	if (getMaterial->vecDiffuseTexture.capacity() <= RegisterNumber)
		getMaterial->vecDiffuseTexture.resize(RegisterNumber + 1);

	getMaterial->vecDiffuseTexture[RegisterNumber] = ResourceManager::Get()->FindTexture(KeyName);
}

void JEONG::Material_Com::SetDiffuseTexture(int RegisterNumber, Texture * pTexture, int Container, int Subset)
{
	if (Container >= m_vecMaterial.size())
	{
		vector<JEONG::SubsetMaterial*> newVec;
		m_vecMaterial.push_back(newVec);
	}

	if (Subset >= m_vecMaterial[Container].size())
		m_vecMaterial[Container].push_back(CreateSubSet());

	JEONG::SubsetMaterial* getMaterial = m_vecMaterial[Container][Subset];
	pTexture->AddRefCount();

	if (getMaterial->vecDiffuseTexture.capacity() <= RegisterNumber)
		getMaterial->vecDiffuseTexture.resize(RegisterNumber + 1);

	getMaterial->vecDiffuseTexture[RegisterNumber] = pTexture;
}

void JEONG::Material_Com::SetDiffuseTextureFromFullPath(int RegisterNumber, const string & KeyName, const TCHAR * FullPath, int Container, int Subset)
{
	if (Container >= m_vecMaterial.size())
	{
		vector<JEONG::SubsetMaterial*> newVec;
		m_vecMaterial.push_back(newVec);
	}

	if (Subset >= m_vecMaterial[Container].size())
	{
		JEONG::SubsetMaterial* newMaterial = new JEONG::SubsetMaterial();
		m_vecMaterial[Container].push_back(newMaterial);
	}

	JEONG::SubsetMaterial *getMaterial = m_vecMaterial[Container][Subset];

	ResourceManager::Get()->CreateTextureFromFullPath(KeyName, FullPath);
	getMaterial->vecDiffuseTexture[RegisterNumber] = ResourceManager::Get()->FindTexture(KeyName);
}

//�� �Լ��� ���� �ȵ���.
void JEONG::Material_Com::SetSampler(int RegisterNumber, const string & KeyName, int Container, int Subset)
{
	//Sampler�� �����Ѵ�.
	if (Container >= m_vecMaterial.size())
	{
		vector<JEONG::SubsetMaterial*> newVec;
		m_vecMaterial.push_back(newVec);
	}

	if (Subset >= m_vecMaterial[Container].size())
	{
		JEONG::SubsetMaterial* newMaterial = new JEONG::SubsetMaterial();
		m_vecMaterial[Container].push_back(newMaterial);
	}

	JEONG::SubsetMaterial* getMaterial = m_vecMaterial[Container][Subset];

	if (getMaterial->vecDiffuseSampler.capacity() <= RegisterNumber)
		getMaterial->vecDiffuseSampler.resize(RegisterNumber + 1);

	//�⺻������ ������ ���÷��� ã�ƿ´�.
	getMaterial->vecDiffuseSampler[RegisterNumber] = ResourceManager::Get()->FindSampler(KeyName);
}

//���̴��� �����Ѵ�.
void JEONG::Material_Com::SetShader(int Container, int Subset)
{
	JEONG::SubsetMaterial* getMaterial = m_vecMaterial[Container][Subset];

	GET_SINGLE(ShaderManager)->UpdateCBuffer("Material", &getMaterial->MatrialInfo);

	for (size_t i = 0; i < getMaterial->vecDiffuseTexture.size(); i++)
	{
		if (getMaterial->vecDiffuseTexture[i] != NULLPTR)
			getMaterial->vecDiffuseTexture[i]->SetShaderResource((int)i); //PSSetResourceView
	}

	for (size_t i = 0; i < getMaterial->vecDiffuseSampler.size(); i++)
	{
		if (getMaterial->vecDiffuseSampler[i] != NULLPTR)
			getMaterial->vecDiffuseSampler[i]->SetSamplerState((int)i); //PSSetResourceView
	}
}

JEONG::SubsetMaterial* JEONG::Material_Com::CreateSubSet()
{
	JEONG::SubsetMaterial* newSubset = new JEONG::SubsetMaterial();
	newSubset->vecDiffuseSampler.push_back(ResourceManager::Get()->FindSampler(LINER_SAMPLER));

	return newSubset;
}

//#include "material.h"
//
//#include "Resource/resource_manager.h"
//#include "Resource/texture.h"
//#include "Resource/sampler.h"
//#include "Rendering/rendering_manager.h"
//
//using namespace DG;
//
//void Material::Initialize()
//{
//	type_ = COMPONENT_TYPE::MATERIAL;
//}
//
//void Material::SetToShader(int _container_idx, int _subset_idx)
//{
//	auto const& subset_material = material_container_vector_.at(_container_idx).at(_subset_idx);
//
//	for (int i = 0; i < subset_material->texture_vector.size(); ++i)
//	{
//		auto const& texture = subset_material->texture_vector.at(i);
//
//		if (texture)
//			texture->SetToShader(i);
//	}
//
//	for (int i = 0; i < subset_material->sampler_vector.size(); ++i)
//	{
//		auto const& sampler = subset_material->sampler_vector.at(i);
//
//		if (sampler)
//			sampler->SetToShader(i);
//	}
//
//	RenderingManager::singleton()->UpdateConstantBuffer("Material", &subset_material->material_constant_buffer);
//}
//
//void Material::SetTexture(std::string const& _tag, int _slot, int _container_idx, int _subset_idx)
//{
//	if (_container_idx >= material_container_vector_.size())
//		material_container_vector_.resize(_container_idx + 1);
//
//	if (_subset_idx >= material_container_vector_.at(_container_idx).size())
//		material_container_vector_.at(_container_idx).resize(_subset_idx + 1);
//
//	if (!material_container_vector_.at(_container_idx).at(_subset_idx))
//	{
//		material_container_vector_.at(_container_idx).at(_subset_idx) = std::shared_ptr<SubsetMaterial>{ new SubsetMaterial, [](SubsetMaterial* _p) {
//		   delete _p;
//		} };
//	}
//
//	auto const& subset_material = material_container_vector_.at(_container_idx).at(_subset_idx);
//
//	if (subset_material->texture_vector.capacity() <= _slot)
//		subset_material->texture_vector.resize(_slot + 1);
//
//	subset_material->texture_vector.at(_slot) = ResourceManager::singleton()->FindTexture(_tag);
//}
//
//void Material::SetSampler(std::string const& _tag, int _slot, int _container_idx, int _subset_idx)
//{
//	if (_container_idx >= material_container_vector_.size())
//		material_container_vector_.resize(_container_idx + 1);
//
//	if (_subset_idx >= material_container_vector_.at(_container_idx).size())
//		material_container_vector_.at(_container_idx).resize(_subset_idx + 1);
//
//	if (!material_container_vector_.at(_container_idx).at(_subset_idx))
//	{
//		material_container_vector_.at(_container_idx).at(_subset_idx) = std::shared_ptr<SubsetMaterial>{ new SubsetMaterial, [](SubsetMaterial* _p) {
//		   delete _p;
//		} };
//	}
//
//	auto const& subset_material = material_container_vector_.at(_container_idx).at(_subset_idx);
//
//	if (subset_material->sampler_vector.capacity() <= _slot)
//		subset_material->sampler_vector.resize(_slot + 1);
//
//	subset_material->sampler_vector.at(_slot) = ResourceManager::singleton()->FindSampler(_tag);
//}
//
//void Material::SetMaterialConstantBuffer(MaterialConstantBuffer const& _material_constant_buffer, int _container_idx, int _subset_idx)
//{
//	if (_container_idx >= material_container_vector_.size())
//		material_container_vector_.resize(_container_idx + 1);
//
//	if (_subset_idx >= material_container_vector_.at(_container_idx).size())
//		material_container_vector_.at(_container_idx).resize(_subset_idx + 1);
//
//	if (!material_container_vector_.at(_container_idx).at(_subset_idx))
//	{
//		material_container_vector_.at(_container_idx).at(_subset_idx) = std::shared_ptr<SubsetMaterial>{ new SubsetMaterial, [](SubsetMaterial* _p) {
//		   delete _p;
//		} };
//	}
//
//	material_container_vector_.at(_container_idx).at(_subset_idx)->material_constant_buffer = _material_constant_buffer;
//}
//
//Material::Material(Material const& _other) : Component(_other)
//{
//	material_container_vector_ = _other.material_container_vector_;
//}
//
//Material::Material(Material&& _other) noexcept : Component(std::move(_other))
//{
//	material_container_vector_ = std::move(_other.material_container_vector_);
//}
//
//void Material::_Release()
//{
//}
//
//std::unique_ptr<Component, std::function<void(Component*)>> Material::_Clone() const
//{
//	return std::unique_ptr<Component, std::function<void(Component*)>>{ new Material{ *this }, [](Component* _p) {
//		dynamic_cast<Material*>(_p)->_Release();
//		delete dynamic_cast<Material*>(_p);
//	} };
//}
