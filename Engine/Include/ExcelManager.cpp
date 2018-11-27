#include "stdafx.h"
#include "ExcelManager.h"

JEONG_USING
SINGLETON_VAR_INIT(ExcelManager)

ExcelManager::ExcelManager()
{
}

ExcelManager::~ExcelManager()
{
	unordered_map<string, ExcelData*>::iterator StartIter = m_ExcelDataMap.begin();
	unordered_map<string, ExcelData*>::iterator EndIter = m_ExcelDataMap.end();

	for (; StartIter != EndIter; StartIter++)
	{
		SAFE_DELETE(StartIter->second);
	}
}

bool ExcelManager::Init()
{
	CreateExcel("AnimationData");

	for (size_t i = 0; i < 10; i++)
	{
		WriteIntData("AnimationData", Vector2(0.0f, (float)i), (int)i);
	}

	return true;
}

void ExcelManager::WriteIntData(const string & KeyName, const Vector2 & CellNumber, const int & Data)
{
	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
		return;

	getData->sheet->writeNum((int)(CellNumber.y + 1.0f), (int)(CellNumber.x), (double)Data);
	SaveExcel(KeyName);
}

void ExcelManager::WriteStringData(const string & KeyName, const Vector2 & CellNumber, const string & Data)
{
	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
		return;

	wstring Temp = CA2W(Data.c_str());
	getData->sheet->writeStr((int)(CellNumber.y + 1.0f), (int)CellNumber.x, Temp.c_str());

	SaveExcel(KeyName);
}

void ExcelManager::WriteFloatData(const string & KeyName, const Vector2 & CellNumber, const float & Data)
{
	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
		return;

	getData->sheet->writeNum((int)(CellNumber.y + 1.0f), (int)(CellNumber.x), (float)Data);
	SaveExcel(KeyName);
}

void ExcelManager::WriteDoubleData(const string & KeyName, const Vector2 & CellNumber, const double & Data)
{
	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
		return;

	getData->sheet->writeNum((int)(CellNumber.y + 1.0f), (int)(CellNumber.x), Data);
	SaveExcel(KeyName);
}

void ExcelManager::WriteBoolData(const string & KeyName, const Vector2 & CellNumber, const bool & Data)
{
	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
		return;

	getData->sheet->writeBool((int)(CellNumber.y + 1.0f), (int)(CellNumber.x), Data);
	SaveExcel(KeyName);
}

int ExcelManager::ReadIntData(const string & KeyName, const Vector2 & CellNumber)
{
	if (LoadExcel(KeyName) == false)
		return 0;

	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
	{
		TrueAssert(true);
		return false;
	}
	
	return (int)getData->sheet->readNum((int)(CellNumber.y + 1.0f), (int)CellNumber.x);
}

string ExcelManager::ReadStringData(const string & KeyName, const Vector2 & CellNumber)
{
	string a = "";

	if (LoadExcel(KeyName) == false)
		return a;

	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
	{
		TrueAssert(true);
		return a;
	}

	wstring Temp = getData->sheet->readStr((int)(CellNumber.y + 1.0f), (int)CellNumber.x);
	string ReturnString = CW2A(Temp.c_str());

	return ReturnString;
}

float ExcelManager::ReadFloatData(const string & KeyName, const Vector2 & CellNumber)
{
	if (LoadExcel(KeyName) == false)
		return 0;

	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
	{
		TrueAssert(true);
		return -1.0f;
	}

	return (float)getData->sheet->readNum((int)(CellNumber.y + 1.0f), (int)CellNumber.x);
}

double ExcelManager::ReadDoubleData(const string & KeyName, const Vector2 & CellNumber)
{
	if (LoadExcel(KeyName) == false)
		return -1.0f;

	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
	{
		TrueAssert(true);
		return -1.0f;
	}

	return getData->sheet->readNum((int)(CellNumber.y + 1.0f), (int)CellNumber.x);
}

bool ExcelManager::ReadBoolData(const string & KeyName, const Vector2 & CellNumber)
{
	if (LoadExcel(KeyName) == false)
		return false;

	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
	{
		TrueAssert(true);
		return false;
	}

	return getData->sheet->readBool((int)(CellNumber.y + 1.0f), (int)CellNumber.x);
}

bool ExcelManager::CreateExcel(const string & KeyName)
{
	ExcelData* newData = FindExcelData(KeyName);

	if (newData != NULLPTR)
		return false;

	wstring Temp = CA2W(KeyName.c_str());

	newData = new ExcelData();
	newData->book = xlCreateBookW();
	newData->sheet = newData->book->addSheet(Temp.c_str());

	m_ExcelDataMap.insert(make_pair(KeyName, newData));
	return true;
}

void ExcelManager::AddSheet(const string & KeyName, const string & SheetName)
{
	ExcelData* getData = FindExcelData(KeyName);
	
	if (getData == NULLPTR)
		return;

	wstring Temp = CA2W(SheetName.c_str());
	getData->book->addSheet(Temp.c_str());
}

ExcelData * ExcelManager::FindExcelData(const string & KeyName)
{
	unordered_map<string, ExcelData*>::iterator FindIter = m_ExcelDataMap.find(KeyName);

	if (FindIter == m_ExcelDataMap.end())
		return NULLPTR;

	return FindIter->second;
}

void ExcelManager::SaveExcel(const string& KeyName, const string& PathKey)
{
	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
		return;

	wstring Path = PathManager::Get()->FindPath(PathKey);

	if (Path.empty() == true)
		return;

	wstring Temp = CA2W(KeyName.c_str());
	Path += Temp;
	Path += L".xls";

	getData->book->save(Path.c_str());
}

bool ExcelManager::LoadExcel(const string& KeyName, const string& PathKey)
{
	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
		return NULLPTR;

	wstring Path = PathManager::Get()->FindPath(PathKey);

	if (Path.empty() == true)
	{
		TrueAssert(true);
		return false;
	}

	wstring Temp = CA2W(KeyName.c_str());
	Path += Temp;
	Path += L".xls";
	
	return getData->book->load(Path.c_str());
}