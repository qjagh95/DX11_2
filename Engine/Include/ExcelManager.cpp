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
	//Sample
	/*
	for (size_t i = 0; i < 10; i++)
	{
		WriteIntData("AnimationData", Vector2(0.0f, (float)i), (int)i);
	}

	for (size_t i = 0; i < 10; i++)
	{
		WriteVector2Data("Temp", Vector2(0.0f, i + 1), Vector2(i * 2, i * 5));
		WriteVector3Data("Temp", Vector2(0.0f, i + 15), Vector3(i * 2, i * 5, i * 10));
		WriteVector4Data("Temp", Vector2(0.0f, i + 35), Vector4(i * 2, i * 5, i * 20, i * 30));
	}

	vector<Vector2> a;
	vector<Vector3> b;
	vector<Vector4> c;

	for (size_t i = 0; i < 10; i++)
	{
		a.push_back(ReadVector2Data("Temp2", Vector2(0.0f, i + 1)));
		b.push_back(ReadVector3Data("Temp2", Vector2(0.0f, i + 15)));
		c.push_back(ReadVector4Data("Temp2", Vector2(0.0f, i + 35)));
	}
	*/
	return true;
}

void ExcelManager::WriteIntData(const string & KeyName, const Vector2 & CellNumber, const int & Data)
{
	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
		getData = CreateExcel(KeyName);

	getData->sheet->writeNum((int)(CellNumber.y + 1.0f), (int)(CellNumber.x), (double)Data);

	if (SaveExcel(KeyName) == false)
	{
		TrueAssert(true);
		return;
	}
}

void ExcelManager::WriteStringData(const string & KeyName, const Vector2 & CellNumber, const string & Data)
{
	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
		getData = CreateExcel(KeyName);

	wstring Temp = CA2W(Data.c_str());
	getData->sheet->writeStr((int)(CellNumber.y + 1.0f), (int)CellNumber.x, Temp.c_str());

	if (SaveExcel(KeyName) == false)
	{
		TrueAssert(true);
		return;
	}
}

void ExcelManager::WriteWStringData(const string & KeyName, const Vector2 & CellNumber, const wstring & Data)
{
	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
		getData = CreateExcel(KeyName);

	getData->sheet->writeStr((int)(CellNumber.y + 1.0f), (int)CellNumber.x, Data.c_str());

	if (SaveExcel(KeyName) == false)
	{
		TrueAssert(true);
		return;
	}
}

void ExcelManager::WriteFloatData(const string & KeyName, const Vector2 & CellNumber, const float & Data)
{
	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
		getData = CreateExcel(KeyName);

	getData->sheet->writeNum((int)(CellNumber.y + 1.0f), (int)(CellNumber.x), (float)Data);

	if (SaveExcel(KeyName) == false)
	{
		TrueAssert(true);
		return;
	}
}

void ExcelManager::WriteDoubleData(const string & KeyName, const Vector2 & CellNumber, const double & Data)
{
	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
		getData = CreateExcel(KeyName);

	getData->sheet->writeNum((int)(CellNumber.y + 1.0f), (int)(CellNumber.x), Data);

	if (SaveExcel(KeyName) == false)
	{
		TrueAssert(true);
		return;
	}
}

void ExcelManager::WriteBoolData(const string & KeyName, const Vector2 & CellNumber, const bool & Data)
{
	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
		getData = CreateExcel(KeyName);

	getData->sheet->writeBool((int)(CellNumber.y + 1.0f), (int)CellNumber.x, Data);

	if (SaveExcel(KeyName) == false)
	{
		TrueAssert(true);
		return;
	}
}

void ExcelManager::WriteVector2Data(const string & KeyName, const Vector2 & CellNumber, const Vector2 & Data)
{
	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
		getData = CreateExcel(KeyName);

	getData->sheet->writeNum((int)(CellNumber.y + 1.0f), (int)CellNumber.x, (double)Data.x);
	getData->sheet->writeNum((int)(CellNumber.y + 1.0f), (int)(CellNumber.x + 1.0f), (double)Data.y);

	if (SaveExcel(KeyName) == false)
	{
		TrueAssert(true);
		return;
	}
}

void ExcelManager::WriteVector3Data(const string & KeyName, const Vector2 & CellNumber, const Vector3 & Data)
{
	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
		getData = CreateExcel(KeyName);

	getData->sheet->writeNum((int)(CellNumber.y + 1.0f), (int)CellNumber.x, (double)Data.x);
	getData->sheet->writeNum((int)(CellNumber.y + 1.0f), (int)(CellNumber.x + 1.0f), (double)Data.y);
	getData->sheet->writeNum((int)(CellNumber.y + 1.0f), (int)(CellNumber.x + 2.0f), (double)Data.z);

	if (SaveExcel(KeyName) == false)
	{
		TrueAssert(true);
		return;
	}
}

void ExcelManager::WriteVector4Data(const string & KeyName, const Vector2 & CellNumber, const Vector4 & Data)
{
	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
		getData = CreateExcel(KeyName);

	getData->sheet->writeNum((int)(CellNumber.y + 1.0f), (int)CellNumber.x, (double)Data.x);
	getData->sheet->writeNum((int)(CellNumber.y + 1.0f), (int)(CellNumber.x + 1.0f), (double)Data.y);
	getData->sheet->writeNum((int)(CellNumber.y + 1.0f), (int)(CellNumber.x + 2.0f), (double)Data.z);
	getData->sheet->writeNum((int)(CellNumber.y + 1.0f), (int)(CellNumber.x + 3.0f), (double)Data.w);

	if (SaveExcel(KeyName) == false)
	{
		TrueAssert(true);
		return;
	}
}

void ExcelManager::WriteIntData(const string & KeyName, size_t CellX, size_t CellY, const int & Data)
{
	WriteIntData(KeyName, Vector2((float)CellX, (float)CellY), Data);
}

void ExcelManager::WriteStringData(const string & KeyName, size_t CellX, size_t CellY, const string & Data)
{
	WriteStringData(KeyName, Vector2((float)CellX, (float)CellY), Data);
}

void ExcelManager::WriteWStringData(const string & KeyName, size_t CellX, size_t CellY, const wstring & Data)
{
	WriteWStringData(KeyName, Vector2((float)CellX, (float)CellY), Data);
}

void ExcelManager::WriteFloatData(const string & KeyName, size_t CellX, size_t CellY, const float & Data)
{
	WriteFloatData(KeyName, Vector2((float)CellX, (float)CellY), Data);
}

void ExcelManager::WriteDoubleData(const string & KeyName, size_t CellX, size_t CellY, const double & Data)
{
	WriteDoubleData(KeyName, Vector2((float)CellX, (float)CellY), Data);
}

void ExcelManager::WriteBoolData(const string & KeyName, size_t CellX, size_t CellY, const bool & Data)
{
	WriteBoolData(KeyName, Vector2((float)CellX, (float)CellY), Data);
}

void ExcelManager::WriteVector2Data(const string & KeyName, size_t CellX, size_t CellY, const Vector2 & Data)
{
	WriteVector2Data(KeyName, Vector2((float)CellX, (float)CellY), Data);
}

void ExcelManager::WriteVector3Data(const string & KeyName, size_t CellX, size_t CellY, const Vector3 & Data)
{
	WriteVector3Data(KeyName, Vector2((float)CellX, (float)CellY), Data);
}

void ExcelManager::WriteVector4Data(const string & KeyName, size_t CellX, size_t CellY, const Vector4 & Data)
{
	WriteVector4Data(KeyName, Vector2((float)CellX, (float)CellY), Data);
}

int ExcelManager::ReadIntData(const string & KeyName, const Vector2 & CellNumber, int SheetIndex)
{
	if (LoadExcel(KeyName) == false)
		return 0;

	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
	{
		TrueAssert(true);
		return false;
	}
	Sheet* getSheet = getData->book->getSheet(SheetIndex);
	getData->sheet = getSheet;

	return (int)getData->sheet->readNum((int)(CellNumber.y + 1.0f), (int)CellNumber.x);
}

string ExcelManager::ReadStringData(const string & KeyName, const Vector2 & CellNumber, int SheetIndex)
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

	Sheet* getSheet = getData->book->getSheet(SheetIndex);
	getData->sheet = getSheet;

	wstring Temp = getSheet->readStr((int)(CellNumber.y + 1.0f), (int)CellNumber.x);
	string ReturnString = CW2A(Temp.c_str());

	return ReturnString;
}

wstring ExcelManager::ReadWStringData(const string & KeyName, const Vector2 & CellNumber, int SheetIndex)
{
	wstring a = L"";

	if (LoadExcel(KeyName) == false)
		return a;

	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
	{
		TrueAssert(true);
		return a;
	}

	Sheet* getSheet = getData->book->getSheet(SheetIndex);
	getData->sheet = getSheet;

	wstring Temp = getSheet->readStr((int)(CellNumber.y + 1.0f), (int)CellNumber.x);
	return Temp;
}

float ExcelManager::ReadFloatData(const string & KeyName, const Vector2 & CellNumber, int SheetIndex)
{
	if (LoadExcel(KeyName) == false)
		return 0;

	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
	{
		TrueAssert(true);
		return -1.0f;
	}
	Sheet* getSheet = getData->book->getSheet(SheetIndex);
	getData->sheet = getSheet;
	
	return (float)getSheet->readNum((int)(CellNumber.y + 1.0f), (int)CellNumber.x);
}

double ExcelManager::ReadDoubleData(const string & KeyName, const Vector2 & CellNumber, int SheetIndex)
{
	if (LoadExcel(KeyName) == false)
		return -1.0f;

	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
	{
		TrueAssert(true);
		return -1.0f;
	}
	Sheet* getSheet = getData->book->getSheet(SheetIndex);
	getData->sheet = getSheet;

	return getSheet->readNum((int)(CellNumber.y + 1.0f), (int)CellNumber.x);
}

bool ExcelManager::ReadBoolData(const string & KeyName, const Vector2 & CellNumber, int SheetIndex)
{
	if (LoadExcel(KeyName) == false)
		return false;

	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
	{
		TrueAssert(true);
		return false;
	}
	Sheet* getSheet = getData->book->getSheet(SheetIndex);
	getData->sheet = getSheet;

	return getSheet->readBool((int)(CellNumber.y + 1.0f), (int)CellNumber.x);
}

Vector2 ExcelManager::ReadVector2Data(const string & KeyName, const Vector2 & CellNumber, int SheetIndex)
{
	if (LoadExcel(KeyName) == false)
		return Vector2();

	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
	{
		TrueAssert(true);
		return false;
	}

	Sheet* getSheet = getData->book->getSheet(SheetIndex);
	getData->sheet = getSheet;

	Vector2 ReturnValue = Vector2((float)getSheet->readNum((int)(CellNumber.y + 1.0f), (int)CellNumber.x),
						  (float)getSheet->readNum((int)(CellNumber.y + 1.0f), (int)(CellNumber.x + 1.0f)));
	return ReturnValue;
}

Vector3 ExcelManager::ReadVector3Data(const string & KeyName, const Vector2 & CellNumber, int SheetIndex)
{
	if (LoadExcel(KeyName) == false)
		return Vector3();

	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
	{
		TrueAssert(true);
		return false;
	}

	Sheet* getSheet = getData->book->getSheet(SheetIndex);
	getData->sheet = getSheet;

	Vector3 ReturnValue = Vector3((float)getSheet->readNum((int)(CellNumber.y + 1.0f), (int)CellNumber.x),
						  (float)getSheet->readNum((int)(CellNumber.y + 1.0f), (int)(CellNumber.x + 1.0f)),
						  (float)getSheet->readNum((int)(CellNumber.y + 1.0f), (int)(CellNumber.x + 2.0f)));

	return ReturnValue;
}

Vector4 ExcelManager::ReadVector4Data(const string & KeyName, const Vector2 & CellNumber, int SheetIndex)
{
	if (LoadExcel(KeyName) == false)
		return Vector4();

	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
	{
		TrueAssert(true);
		return false;
	}

	Sheet* getSheet = getData->book->getSheet(SheetIndex);
	getData->sheet = getSheet;

	Vector4 ReturnValue = Vector4((float)getSheet->readNum((int)(CellNumber.y + 1.0f), (int)CellNumber.x),
						  (float)getSheet->readNum((int)(CellNumber.y + 1.0f), (int)(CellNumber.x + 1.0f)),
						  (float)getSheet->readNum((int)(CellNumber.y + 1.0f), (int)(CellNumber.x + 2.0f)),
						  (float)getSheet->readNum((int)(CellNumber.y + 1.0f), (int)(CellNumber.x + 3.0f)));

	return ReturnValue;
}

int ExcelManager::ReadIntData(const string & KeyName, size_t CellX, size_t CellY, int SheetIndex)
{
	return ReadIntData(KeyName, Vector2((float)CellX, (float)CellY), SheetIndex);
}

string ExcelManager::ReadStringData(const string & KeyName, size_t CellX, size_t CellY, int SheetIndex)
{
	return ReadStringData(KeyName, Vector2((float)CellX, (float)CellY), SheetIndex);
}

wstring ExcelManager::ReadWStringData(const string & KeyName, size_t CellX, size_t CellY, int SheetIndex)
{
	return ReadWStringData(KeyName, Vector2((float)CellX, (float)CellY), SheetIndex);
}

float ExcelManager::ReadFloatData(const string & KeyName, size_t CellX, size_t CellY, int SheetIndex)
{
	return ReadFloatData(KeyName, Vector2((float)CellX, (float)CellY), SheetIndex);
}

double ExcelManager::ReadDoubleData(const string & KeyName, size_t CellX, size_t CellY, int SheetIndex)
{
	return ReadDoubleData(KeyName, Vector2((float)CellX, (float)CellY), SheetIndex);
}

bool ExcelManager::ReadBoolData(const string & KeyName, size_t CellX, size_t CellY, int SheetIndex)
{
	return ReadBoolData(KeyName, Vector2((float)CellX, (float)CellY), SheetIndex);
}

Vector2 ExcelManager::ReadVector2Data(const string & KeyName, size_t CellX, size_t CellY, int SheetIndex)
{
	return ReadVector2Data(KeyName, Vector2((float)CellX, (float)CellY), SheetIndex);
}

Vector3 ExcelManager::ReadVector3Data(const string & KeyName, size_t CellX, size_t CellY, int SheetIndex)
{
	return ReadVector3Data(KeyName, Vector2((float)CellX, (float)CellY), SheetIndex);
}

Vector4 ExcelManager::ReadVector4Data(const string & KeyName, size_t CellX, size_t CellY, int SheetIndex)
{
	return ReadVector4Data(KeyName, Vector2((float)CellX, (float)CellY), SheetIndex);
}

ExcelData* ExcelManager::CreateExcel(const string & KeyName)
{
	ExcelData* newData = FindExcelData(KeyName);

	if (newData != NULLPTR)
		return newData;

	wstring Temp = CA2W(KeyName.c_str());

	newData = new ExcelData();
	newData->book = xlCreateBookW();
	newData->sheet = newData->book->addSheet(Temp.c_str());

	m_ExcelDataMap.insert(make_pair(KeyName, newData));

	return newData;
}

void ExcelManager::AddSheet(const string & KeyName, const string & SheetName)
{
	ExcelData* getData = FindExcelData(KeyName);
	
	if (getData == NULLPTR)
	{
		TrueAssert(true);
		return;
	}

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

bool ExcelManager::SaveExcel(const string& KeyName, const string& PathKey)
{
	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
		return false;

	wstring Path = PathManager::Get()->FindPath(PathKey);

	if (Path.empty() == true)
		return false;

	wstring Temp = CA2W(KeyName.c_str());
	Path += Temp;
	Path += L".xls";

	return getData->book->save(Path.c_str());
}

bool ExcelManager::LoadExcel(const string& KeyName, const string& PathKey)
{
	ExcelData* getData = FindExcelData(KeyName);

	if (getData == NULLPTR)
	{
		CreateExcel(KeyName);
		return true;
	}

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