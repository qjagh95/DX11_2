#pragma once
JEONG_BEGIN
class JEONG_DLL BineryWrite
{
public:
	void WriteBool(bool Data);
	void WriteInt(int Data);
	void WriteFloat(float Data);
	void WriteDouble(double Data);

	void WriteVector2(const Vector2& Data);
	void WriteVector3(const Vector3& Data);
	void WriteVector4(const Vector4& Data);
	void WriteMatrix(const Matrix& Data);

	void WriteString(const string& Data);

private:
	HANDLE m_FileHandle;
	DWORD m_Size;

private:
	BineryWrite(string FileName, UINT OpenOption = CREATE_ALWAYS);
	BineryWrite(wstring FileName, UINT OpenOption = CREATE_ALWAYS);
	~BineryWrite();
};

JEONG_END
