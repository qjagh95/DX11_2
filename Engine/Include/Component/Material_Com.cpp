#include "Material_Com.h"
#include "Animation2D_Com.h"

#include "../GameObject.h"

#include "../Resource/ResourceManager.h"
#include "../Resource/Sampler.h"
#include "../Resource/Texture.h"

#include "../Render/ShaderManager.h"

JEONG_USING

Material_Com::Material_Com()
{
	m_ComType = CT_MATERIAL;
}

Material_Com::Material_Com(const Material_Com& copyData)
	:Component_Base(copyData)
{
 	m_vecMaterial.clear();

	for (size_t i = 0; i < copyData.m_vecMaterial.size(); i++)
	{
		vector<SubsetMaterial*> TempVec;
		m_vecMaterial.push_back(TempVec);

		for (size_t j = 0; j < copyData.m_vecMaterial[i].size(); j++)
		{
			SubsetMaterial*	newMaterial = new SubsetMaterial();
			newMaterial->MatrialInfo = copyData.m_vecMaterial[i][j]->MatrialInfo;
			newMaterial->DiffuseTexture = copyData.m_vecMaterial[i][j]->DiffuseTexture;
			newMaterial->TextureRegister = copyData.m_vecMaterial[i][j]->TextureRegister;
			newMaterial->DiffuseSampler = copyData.m_vecMaterial[i][j]->DiffuseSampler;
			newMaterial->SamplerRegister = copyData.m_vecMaterial[i][j]->SamplerRegister;

			if (newMaterial->DiffuseTexture != NULLPTR)
				newMaterial->DiffuseTexture->AddRefCount();

			if (newMaterial->DiffuseSampler != NULLPTR)
				newMaterial->DiffuseSampler->AddRefCount();

			m_vecMaterial[i].push_back(newMaterial);
		}
	}
}

Material_Com::~Material_Com()
{
	for (size_t i = 0; i < m_vecMaterial.size(); ++i)
	{
		for (size_t j = 0; j < m_vecMaterial[i].size(); ++j)
		{
			SAFE_RELEASE(m_vecMaterial[i][j]->DiffuseTexture);
			SAFE_RELEASE(m_vecMaterial[i][j]->DiffuseSampler);
			SAFE_DELETE(m_vecMaterial[i][j]);
		}
		m_vecMaterial[i].clear();
	}
	m_vecMaterial.clear();
}

bool Material_Com::Init()
{
	SetMaterial(Vector4::White);

	return true;
}

int Material_Com::Input(float DeltaTime)
{
	return 0;
}

int Material_Com::Update(float DeltaTime)
{
	return 0;
}

int Material_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Material_Com::Collision(float DeltaTime)
{
}

void Material_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Material_Com::Render(float DeltaTime)
{
}

Material_Com * Material_Com::Clone()
{
	return new Material_Com(*this);
}

void Material_Com::SetMaterial(const Vector4 & Diffuse, int Container, int Subset)
{
	//�����̳ʰ� ���ٸ� �ϳ� �߰��Ѵ�.
	if (Container >= m_vecMaterial.size())
	{
		vector<SubsetMaterial*>	newVec;
		m_vecMaterial.push_back(newVec);
	}
	//������� ���ٸ� �߰��Ѵ�.
	if (Subset >= m_vecMaterial[Container].size())
		m_vecMaterial[Container].push_back(CreateSubSet());

	//������������
	m_vecMaterial[Container][Subset]->MatrialInfo.Diffuse = Diffuse;
}

void Material_Com::SetDiffuseTexture(int RegisterNumber, const string & KeyName, int Container, int Subset)
{
	//�����̳ʰ� ���ٸ� �ϳ� �߰��Ѵ�.
	if (Container >= m_vecMaterial.size())
	{
		vector<SubsetMaterial*>	newVec;
		m_vecMaterial.push_back(newVec);
	}
	//������� ���ٸ� �߰��Ѵ�.
	if (Subset >= m_vecMaterial[Container].size())
		m_vecMaterial[Container].push_back(CreateSubSet());

	//�ؽ��� �����غ�
	SubsetMaterial*	pMaterial = m_vecMaterial[Container][Subset];
	SAFE_RELEASE(pMaterial->DiffuseTexture);
	//�ؽ��ĸ� Material���� ������ �����Ѵ�.
	pMaterial->DiffuseTexture = ResourceManager::Get()->FindTexture(KeyName);
	//���̴� �������� ��ȣ.
	pMaterial->TextureRegister = RegisterNumber;
}

void Material_Com::SetDiffuseTexture(int RegisterNumber, const string & KeyName, const TCHAR * FileName, const string & PathKey, int Container, int Subset)
{
	if (Container >= m_vecMaterial.size())
	{
		vector<SubsetMaterial*>	newVec;
		m_vecMaterial.push_back(newVec);
	}

	if (Subset >= m_vecMaterial[Container].size())
		m_vecMaterial[Container].push_back(CreateSubSet());

	SubsetMaterial*	getMaterial = m_vecMaterial[Container][Subset];
	SAFE_RELEASE(getMaterial->DiffuseTexture);
	//�ؽ��İ� ���ٸ� �ʿ� �߰��� ��
	ResourceManager::Get()->CreateTexture(KeyName, FileName, PathKey);
	//������ ����.
	getMaterial->DiffuseTexture = ResourceManager::Get()->FindTexture(KeyName);
	getMaterial->TextureRegister = RegisterNumber;
}

void Material_Com::SetDiffuseTexture(int RegisterNumber, Texture * pTexture, int Container, int Subset)
{
	if (Container >= m_vecMaterial.size())
	{
		vector<SubsetMaterial*>	newVec;
		m_vecMaterial.push_back(newVec);
	}

	if (Subset >= m_vecMaterial[Container].size())
		m_vecMaterial[Container].push_back(CreateSubSet());

	SubsetMaterial*	getMaterial = m_vecMaterial[Container][Subset];
	pTexture->AddRefCount();
	
	getMaterial->DiffuseTexture = pTexture;
	getMaterial->TextureRegister = RegisterNumber;
}

void Material_Com::SetDiffuseTextureFromFullPath(int RegisterNumber, const string & KeyName, const TCHAR * FullPath, int Container, int Subset)
{
	if (Container >= m_vecMaterial.size())
	{
		vector<SubsetMaterial*>	newVec;
		m_vecMaterial.push_back(newVec);
	}

	if (Subset >= m_vecMaterial[Container].size())
	{
		SubsetMaterial* newMaterial = new SubsetMaterial();
		m_vecMaterial[Container].push_back(newMaterial);
	}

	SubsetMaterial *getMaterial = m_vecMaterial[Container][Subset];
	SAFE_RELEASE(getMaterial->DiffuseTexture);

	ResourceManager::Get()->CreateTextureFromFullPath(KeyName, FullPath);
	getMaterial->DiffuseTexture = ResourceManager::Get()->FindTexture(KeyName);
	getMaterial->TextureRegister = RegisterNumber;
}

//�� �Լ��� ���� �ȵ���.
void Material_Com::SetSampler(int RegisterNumber, const string & KeyName, int Container, int Subset)
{
	//Sampler�� �����Ѵ�.
	if (Container >= m_vecMaterial.size())
	{
		vector<SubsetMaterial*>	newVec;
		m_vecMaterial.push_back(newVec);
	}

	if (Subset >= m_vecMaterial[Container].size())
	{
		SubsetMaterial* newMaterial = new SubsetMaterial();
		m_vecMaterial[Container].push_back(newMaterial);
	}

	SubsetMaterial*	getMaterial = m_vecMaterial[Container][Subset];
	SAFE_RELEASE(getMaterial->DiffuseSampler);

	//�⺻������ ������ ���÷��� ã�ƿ´�.
	getMaterial->DiffuseSampler = ResourceManager::Get()->FindSampler(KeyName);
	getMaterial->SamplerRegister = RegisterNumber;
}

//���̴��� �����Ѵ�.
void Material_Com::SetShader(int Container, int Subset)
{
	SubsetMaterial*	getMaterial = m_vecMaterial[Container][Subset];

	GET_SINGLE(ShaderManager)->UpdateCBuffer("Material", &getMaterial->MatrialInfo);

	if (getMaterial->DiffuseTexture != NULLPTR) 
		getMaterial->DiffuseTexture->SetShaderResource(getMaterial->TextureRegister); //PSSetResourceView

	if (getMaterial->DiffuseSampler != NULLPTR)
		getMaterial->DiffuseSampler->SetSamplerState(getMaterial->SamplerRegister); //PSSetSampler
}

SubsetMaterial* Material_Com::CreateSubSet()
{
	SubsetMaterial* newSubset = new SubsetMaterial();
	newSubset->DiffuseSampler = ResourceManager::Get()->FindSampler(LINER_SAMPLER);
	return newSubset;
}