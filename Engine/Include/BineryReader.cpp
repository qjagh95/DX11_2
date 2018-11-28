#include "stdafx.h"
#include "BineryReader.h"

JEONG_USING

BineryRead::BineryRead(const string& FileName)
	:m_FileHandle(NULLPTR), m_Size(0)
{
	wstring Temp;
	Temp = PathManager::Get()->FindPath(DATA_PATH);

	if (Temp.empty() == true)
		return;

	Temp += CA2W(FileName.c_str());
	string Temp2 = CW2A(Temp.c_str());

	m_FileHandle = CreateFileA(Temp2.c_str(), GENERIC_READ, FILE_SHARE_READ, NULLPTR, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULLPTR);
}

BineryRead::BineryRead(const wstring& FileName)
	: m_FileHandle(NULLPTR)
{
	wstring Temp;
	Temp = PathManager::Get()->FindPath(DATA_PATH);

	if (Temp.empty() == true)
		return;

	Temp += FileName;
	m_FileHandle = CreateFileW(Temp.c_str(), GENERIC_READ, FILE_SHARE_READ, NULLPTR, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULLPTR);
}

BineryRead::~BineryRead()
{
	if (m_FileHandle != NULLPTR)
	{
		CloseHandle(m_FileHandle);
		m_FileHandle = NULL;
	}
}

bool BineryRead::ReadBool()
{
	bool Temp = false;

	ReadFile(m_FileHandle, &Temp, sizeof(bool), &m_Size, NULLPTR);

	return Temp;
}

int BineryRead::ReadInt()
{
	int Temp = -1;

	ReadFile(m_FileHandle, &Temp, sizeof(int), &m_Size, NULLPTR);

	return Temp;
}

float BineryRead::ReadFloat()
{
	float Temp = -1.0f;

	ReadFile(m_FileHandle, &Temp, sizeof(float), &m_Size, NULLPTR);

	return 0.0f;
}

double BineryRead::ReadDouble()
{
	double Temp = -1.0f;

	ReadFile(m_FileHandle, &Temp, sizeof(double), &m_Size, NULLPTR);

	return Temp;
}
 
Vector2 BineryRead::ReadVector2()
{
	Vector2 Temp;

	ReadFile(m_FileHandle, &Temp, sizeof(Vector2), &m_Size, NULLPTR);

	return Temp;
}

Vector3 BineryRead::ReadVector3()
{
	Vector3 Temp;

	ReadFile(m_FileHandle, &Temp, sizeof(Vector3), &m_Size, NULLPTR);

	return Temp;
}

Vector4 BineryRead::ReadVector4()
{
	Vector4 Temp;

	ReadFile(m_FileHandle, &Temp, sizeof(Vector4), &m_Size, NULLPTR);

	return Temp;
}

Matrix BineryRead::ReadMatrix()
{
	Matrix Temp;

	ReadFile(m_FileHandle, &Temp, sizeof(Matrix), &m_Size, NULLPTR);

	return Temp;
}

string BineryRead::ReadString()
{
	string Temp;
	UINT StringLenth;

	ReadFile(m_FileHandle, &StringLenth, sizeof(UINT), &m_Size, NULLPTR);
	ReadFile(m_FileHandle, &Temp, StringLenth, &m_Size, NULLPTR);

	return Temp;
}
