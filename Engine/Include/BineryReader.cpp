#include "stdafx.h"
#include "BineryReader.h"

JEONG_USING

JEONG::BineryRead::BineryRead(const string& FileName)
{
	wstring Temp;
	Temp = PathManager::Get()->FindPath(DATA_PATH);

	if (Temp.empty() == true)
		return;

	Temp += CA2W(FileName.c_str());
	string Temp2 = CW2A(Temp.c_str());

	m_ReadFile.open(Temp2.c_str(), ios::binary);
}

JEONG::BineryRead::BineryRead(const wstring& FileName)
{
	wstring Temp;
	Temp = PathManager::Get()->FindPath(DATA_PATH);

	if (Temp.empty() == true)
		return;

	Temp += FileName;
	m_ReadFile.open(Temp.c_str());
}

JEONG::BineryRead::~BineryRead()
{
	m_ReadFile.close();
}

bool JEONG::BineryRead::ReadBool()
{
	int Temp = -1;

	m_ReadFile >> Temp;

	if (Temp == -1)
		TrueAssert(true);

	return (bool)Temp;
}

int JEONG::BineryRead::ReadInt()
{
	int Temp = -1;

	m_ReadFile >> Temp;

	if (Temp == -1)
		TrueAssert(true);

	return Temp;
}

float JEONG::BineryRead::ReadFloat()
{
	float Temp = -1.0f;

	m_ReadFile >> Temp;

	if (Temp == -1.0f)
		TrueAssert(true);

	return Temp;
}

double JEONG::BineryRead::ReadDouble()
{
	double Temp = -1.0f;

	m_ReadFile >> Temp;

	if (Temp == -1.0f)
		TrueAssert(true);

	return Temp;
}
 
Vector2 JEONG::BineryRead::ReadVector2()
{
	Vector2 Temp = Vector2(-1.0f, -1.0f);

	m_ReadFile >> Temp.x;
	m_ReadFile >> Temp.y;

	if (Temp == -1.0f)
		TrueAssert(true);

	return Temp;
}

Vector3 JEONG::BineryRead::ReadVector3()
{
	Vector3 Temp = Vector3(-1.0f, -1.0f, -1.0f);

	m_ReadFile >> Temp.x;
	m_ReadFile >> Temp.y;
	m_ReadFile >> Temp.z;

	if (Temp == -1.0f)
		TrueAssert(true);

	return Temp;
}

Vector4 JEONG::BineryRead::ReadVector4()
{
	Vector4 Temp = Vector4(-1.0f, -1.0f, -1.0f, -1.0f);
	
	m_ReadFile >> Temp.x;
	m_ReadFile >> Temp.y;
	m_ReadFile >> Temp.z;
	m_ReadFile >> Temp.w;

	if (Temp == -1.0f)
		TrueAssert(true);

	return Temp;
}

string JEONG::BineryRead::ReadString()
{
	string Temp;

	m_ReadFile >> Temp;

	return Temp;
}

wstring JEONG::BineryRead::ReadWString()
{
	string Temp;
	m_ReadFile >> Temp;
	wstring ReturnString = CA2W(Temp.c_str());

	return ReturnString;
}

void JEONG::BineryRead::ReadData(bool & Data)
{
	m_ReadFile >> Data;
}

void JEONG::BineryRead::ReadData(int & Data)
{
	m_ReadFile >> Data;
}

void JEONG::BineryRead::ReadData(float & Data)
{
	m_ReadFile >> Data;
}

void JEONG::BineryRead::ReadData(double & Data)
{
	m_ReadFile >> Data;
}

void JEONG::BineryRead::ReadData(Vector2 & Data)
{
	m_ReadFile >> Data.x;
	m_ReadFile >> Data.y;
}

void JEONG::BineryRead::ReadData(Vector3 & Data)
{
	m_ReadFile >> Data.x;
	m_ReadFile >> Data.y;
	m_ReadFile >> Data.z;
}

void JEONG::BineryRead::ReadData(Vector4 & Data)
{
	m_ReadFile >> Data.x;
	m_ReadFile >> Data.y;
	m_ReadFile >> Data.z;
	m_ReadFile >> Data.w;
}

void JEONG::BineryRead::ReadData(string & Data)
{
	m_ReadFile >> Data;
}

void JEONG::BineryRead::ReadData(wstring & Data)
{
	string Temp = CW2A(Data.c_str());
	m_ReadFile >> Temp;
}
