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
	void WriteWStringData(const string& KeyName, const Vector2& CellNumber, const wstring& Data);
	void WriteFloatData(const string& KeyName, const Vector2& CellNumber, const float& Data);
	void WriteDoubleData(const string& KeyName, const Vector2& CellNumber, const double& Data);
	void WriteBoolData(const string& KeyName, const Vector2& CellNumber, const bool& Data);
	void WriteVector2Data(const string& KeyName, const Vector2& CellNumber, const Vector2& Data);
	void WriteVector3Data(const string& KeyName, const Vector2& CellNumber, const Vector3& Data);
	void WriteVector4Data(const string& KeyName, const Vector2& CellNumber, const Vector4& Data);

	void WriteIntData(const string& KeyName, size_t CellX, size_t CellY, const int& Data);
	void WriteStringData(const string& KeyName, size_t CellX, size_t CellY, const string& Data);
	void WriteWStringData(const string& KeyName, size_t CellX, size_t CellY, const wstring& Data);
	void WriteFloatData(const string& KeyName, size_t CellX, size_t CellY, const float& Data);
	void WriteDoubleData(const string& KeyName, size_t CellX, size_t CellY, const double& Data);
	void WriteBoolData(const string& KeyName, size_t CellX, size_t CellY, const bool& Data);
	void WriteVector2Data(const string& KeyName, size_t CellX, size_t CellY, const Vector2& Data);
	void WriteVector3Data(const string& KeyName, size_t CellX, size_t CellY, const Vector3& Data);
	void WriteVector4Data(const string& KeyName, size_t CellX, size_t CellY, const Vector4& Data);

	int ReadIntData(const string& KeyName, const Vector2& CellNumber, int SheetIndex = 0);
	string ReadStringData(const string& KeyName, const Vector2& CellNumber, int SheetIndex = 0);
	wstring ReadWStringData(const string& KeyName, const Vector2& CellNumber, int SheetIndex = 0);
	float ReadFloatData(const string& KeyName, const Vector2& CellNumber, int SheetIndex = 0);
	double ReadDoubleData(const string& KeyName, const Vector2& CellNumber, int SheetIndex = 0);
	bool ReadBoolData(const string& KeyName, const Vector2& CellNumber, int SheetIndex = 0);
	Vector2 ReadVector2Data(const string& KeyName, const Vector2& CellNumber, int SheetIndex = 0);
	Vector3 ReadVector3Data(const string& KeyName, const Vector2& CellNumber, int SheetIndex = 0);
	Vector4 ReadVector4Data(const string& KeyName, const Vector2& CellNumber, int SheetIndex = 0);

	int ReadIntData(const string& KeyName, size_t CellX, size_t CellY, int SheetIndex = 0);
	string ReadStringData(const string& KeyName, size_t CellX, size_t CellY, int SheetIndex = 0);
	wstring ReadWStringData(const string& KeyName, size_t CellX, size_t CellY, int SheetIndex = 0);
	float ReadFloatData(const string& KeyName, size_t CellX, size_t CellY, int SheetIndex = 0);
	double ReadDoubleData(const string& KeyName, size_t CellX, size_t CellY, int SheetIndex = 0);
	bool ReadBoolData(const string& KeyName, size_t CellX, size_t CellY, int SheetIndex = 0);
	Vector2 ReadVector2Data(const string& KeyName, size_t CellX, size_t CellY, int SheetIndex = 0);
	Vector3 ReadVector3Data(const string& KeyName, size_t CellX, size_t CellY, int SheetIndex = 0);
	Vector4 ReadVector4Data(const string& KeyName, size_t CellX, size_t CellY, int SheetIndex = 0);

	ExcelData* CreateExcel(const string& KeyName);
	void AddSheet(const string& KeyName, const string& SheetName);

private:
	bool SaveExcel(const string& KeyName, const string& PathKey = DATA_PATH);
	bool LoadExcel(const string& KeyName, const string& PathKey = DATA_PATH);

	ExcelData* FindExcelData(const string& KeyName);

private:
	unordered_map<string, ExcelData*> m_ExcelDataMap;

public:
	CLASS_IN_SINGLE(ExcelManager)
};

JEONG_END


