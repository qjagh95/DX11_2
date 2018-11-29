#include "stdafx.h"
#include "BineryReader.h"

JEONG_USING

BineryRead::BineryRead(const string& FileName)
{
	wstring Temp;
	Temp = PathManager::Get()->FindPath(DATA_PATH);

	if (Temp.empty() == true)
		return;

	Temp += CA2W(FileName.c_str());
	string Temp2 = CW2A(Temp.c_str());

	m_ReadFile.open(Temp2.c_str(), ios::binary);
}

BineryRead::BineryRead(const wstring& FileName)
{
	wstring Temp;
	Temp = PathManager::Get()->FindPath(DATA_PATH);

	if (Temp.empty() == true)
		return;

	Temp += FileName;
	m_ReadFile.open(Temp.c_str());
}

BineryRead::~BineryRead()
{
	m_ReadFile.close();
}

bool BineryRead::ReadBool()
{
	bool Temp = false;

	m_ReadFile >> Temp;

	return Temp;
}

int BineryRead::ReadInt()
{
	int Temp = -1;

	m_ReadFile >> Temp;

	return Temp;
}

float BineryRead::ReadFloat()
{
	float Temp = -1.0f;

	m_ReadFile >> Temp;

	return Temp;
}

double BineryRead::ReadDouble()
{
	double Temp = -1.0f;

	m_ReadFile >> Temp;

	return Temp;
}
 
Vector2 BineryRead::ReadVector2()
{
	Vector2 Temp;

	m_ReadFile >> Temp.x;
	m_ReadFile >> Temp.y;

	return Temp;
}

Vector3 BineryRead::ReadVector3()
{
	Vector3 Temp;

	m_ReadFile >> Temp.x;
	m_ReadFile >> Temp.y;
	m_ReadFile >> Temp.z;

	return Temp;
}

Vector4 BineryRead::ReadVector4()
{
	Vector4 Temp;
	
	m_ReadFile >> Temp.x;
	m_ReadFile >> Temp.y;
	m_ReadFile >> Temp.z;
	m_ReadFile >> Temp.w;

	return Temp;
}

string BineryRead::ReadString()
{
	string Temp;

	m_ReadFile >> Temp;

	return Temp;
}

wstring BineryRead::ReadWString()
{
	string Temp;

	m_ReadFile >> Temp;

	wstring ReturnString = CA2W(Temp.c_str());

	return ReturnString;
}
