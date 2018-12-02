#include "stdafx.h"
#include "BineryWriter.h"

JEONG_USING

JEONG::BineryWrite::BineryWrite(const string& FileName)
{
	wstring Temp;
	Temp = PathManager::Get()->FindPath(DATA_PATH);
	
	if (Temp.empty() == true)
		return;

	Temp += CA2W(FileName.c_str());
	string Temp2 = CW2A(Temp.c_str());

	m_WriteFile.open(Temp2.c_str(), ios::binary);
}

JEONG::BineryWrite::BineryWrite(const wstring& FileName)
{
	wstring Temp;
	Temp = PathManager::Get()->FindPath(DATA_PATH);

	if (Temp.empty() == true)
		return;

	Temp += FileName;

	m_WriteFile.open(Temp.c_str(), ios::binary);
}

JEONG::BineryWrite::~BineryWrite()
{
	m_WriteFile.close();
}

void JEONG::BineryWrite::WriteData(const bool& Data)
{
	m_WriteFile << Data << endl;
}

void JEONG::BineryWrite::WriteData(const int& Data)
{
	m_WriteFile << Data << endl;
}

void JEONG::BineryWrite::WriteData(const float& Data)
{
	m_WriteFile << Data << endl;
}

void JEONG::BineryWrite::WriteData(const double& Data)
{
	m_WriteFile << Data << endl;
}

void JEONG::BineryWrite::WriteData(const Vector2 & Data)
{
	m_WriteFile << Data.x << endl;
	m_WriteFile << Data.y << endl;
}

void JEONG::BineryWrite::WriteData(const Vector3 & Data)
{
	m_WriteFile << Data.x << endl;
	m_WriteFile << Data.y << endl;
	m_WriteFile << Data.z << endl;
}

void JEONG::BineryWrite::WriteData(const Vector4 & Data)
{
	m_WriteFile << Data.x << endl;
	m_WriteFile << Data.y << endl;
	m_WriteFile << Data.z << endl;
	m_WriteFile << Data.w << endl;
}

void JEONG::BineryWrite::WriteData(const string & Data)
{
	m_WriteFile << Data << endl;
}

void JEONG::BineryWrite::WriteData(const wstring & Data)
{
	string Temp = CW2A(Data.c_str());

	m_WriteFile << Temp << endl;
}

void JEONG::BineryWrite::WriteData(const char * Data)
{
	string Temp = Data;

	m_WriteFile << Temp << endl;
}

void JEONG::BineryWrite::WriteData(const wchar_t * Data)
{
	wstring Temp = Data;
	string Temp2 = CW2A(Temp.c_str());

	m_WriteFile << Temp2 << endl;
}
