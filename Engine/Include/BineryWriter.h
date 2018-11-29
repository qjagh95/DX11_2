#pragma once
JEONG_BEGIN
class JEONG_DLL BineryWrite
{
public:
	void WriteData(bool Data);
	void WriteData(int Data);
	void WriteData(float Data);
	void WriteData(double Data);
	void WriteData(const Vector2& Data);
	void WriteData(const Vector3& Data);
	void WriteData(const Vector4& Data);
	void WriteData(const string& Data);
	void WriteData(const wstring& Data);
	void WriteData(const char* Data);
	void WriteData(const wchar_t* Data);

private:
	ofstream m_WriteFile;

private:
	BineryWrite(string FileName);
	BineryWrite(wstring FileName);
	~BineryWrite();
};

JEONG_END
