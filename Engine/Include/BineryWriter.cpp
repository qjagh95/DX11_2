#include "stdafx.h"
#include "BineryWriter.h"

JEONG_USING

BineryWrite::BineryWrite(string FileName, UINT OpenOption)
	:m_FileHandle(NULLPTR), m_Size(0)
{
	wstring Temp;
	Temp = PathManager::Get()->FindPath(DATA_PATH);
	
	if (Temp.empty() == true)
		return;

	Temp += CA2W(FileName.c_str());
	string Temp2 = CW2A(Temp.c_str());

	m_FileHandle = CreateFileA(Temp2.c_str(), GENERIC_WRITE, 0, NULLPTR, OpenOption, FILE_ATTRIBUTE_NORMAL, NULLPTR);
}

BineryWrite::BineryWrite(wstring FileName, UINT OpenOption)
	: m_FileHandle(NULLPTR)
{
	wstring Temp;
	Temp = PathManager::Get()->FindPath(DATA_PATH);

	if (Temp.empty() == true)
		return;

	Temp += FileName;
	m_FileHandle = CreateFileW(Temp.c_str(), GENERIC_WRITE, 0, NULLPTR, OpenOption, FILE_ATTRIBUTE_NORMAL, NULLPTR);
	
}

BineryWrite::~BineryWrite()
{
	if (m_FileHandle != NULLPTR)
	{
		CloseHandle(m_FileHandle);
		m_FileHandle = NULLPTR;
	}
}

void BineryWrite::WriteBool(bool Data)
{
	WriteFile(m_FileHandle, &Data, sizeof(bool), &m_Size, NULLPTR);
}

void BineryWrite::WriteInt(int Data)
{
	WriteFile(m_FileHandle, &Data, sizeof(int), &m_Size, NULLPTR);
}

void BineryWrite::WriteFloat(float Data)
{
	WriteFile(m_FileHandle, &Data, sizeof(float), &m_Size, NULLPTR);
}

void BineryWrite::WriteDouble(double Data)
{
	WriteFile(m_FileHandle, &Data, sizeof(double), &m_Size, NULLPTR);
}

void BineryWrite::WriteVector2(const Vector2 & Data)
{
	WriteFile(m_FileHandle, &Data, sizeof(Vector2), &m_Size, NULLPTR);
}

void BineryWrite::WriteVector3(const Vector3 & Data)
{
	WriteFile(m_FileHandle, &Data, sizeof(Vector3), &m_Size, NULLPTR);
}

void BineryWrite::WriteVector4(const Vector4 & Data)
{
	WriteFile(m_FileHandle, &Data, sizeof(Vector4), &m_Size, NULLPTR);
}

void BineryWrite::WriteMatrix(const Matrix & Data)
{
	WriteFile(m_FileHandle, &Data, sizeof(Matrix), &m_Size, NULLPTR);
}

void BineryWrite::WriteString(const string & Data)
{
	const char* Temp = Data.c_str();
	size_t StringLenth = Data.length();

	WriteFile(m_FileHandle, &StringLenth, sizeof(size_t), &m_Size, NULLPTR);
	WriteFile(m_FileHandle, &Temp, StringLenth, &m_Size, NULLPTR);
}
