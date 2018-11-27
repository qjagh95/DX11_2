#pragma once

JEONG_BEGIN

struct JEONG_DLL ExcelData
{
	Book* book;
	Sheet* sheet;

	ExcelData() { book = NULLPTR, sheet = NULLPTR; }
	~ExcelData() { book->release(); }
};

class JEONG_DLL ExcelManager
{
public:
	bool Init();
	
	void WriteIntData(const string& KeyName, const Vector2& CellNumber, const int& Data);
	void WriteStringData(const string& KeyName, const Vector2& CellNumber, const string& Data);
	void WriteFloatData(const string& KeyName, const Vector2& CellNumber, const float& Data);
	void WriteDoubleData(const string& KeyName, const Vector2& CellNumber, const double& Data);
	void WriteBoolData(const string& KeyName, const Vector2& CellNumber, const bool& Data);

	int ReadIntData(const string& KeyName, const Vector2& CellNumber);
	string ReadStringData(const string& KeyName, const Vector2& CellNumber);
	float ReadFloatData(const string& KeyName, const Vector2& CellNumber);
	double ReadDoubleData(const string& KeyName, const Vector2& CellNumber);
	bool ReadBoolData(const string& KeyName, const Vector2& CellNumber);
	
	bool CreateExcel(const string& KeyName);
	void AddSheet(const string& KeyName, const string& SheetName);

private:
	void SaveExcel(const string& KeyName, const string& PathKey = DATA_PATH);
	bool LoadExcel(const string& KeyName, const string& PathKey = DATA_PATH);

	ExcelData* FindExcelData(const string& KeyName);
	
private:
	unordered_map<string, ExcelData*> m_ExcelDataMap;

public:
	CLASS_IN_SINGLE(ExcelManager)
};

JEONG_END


