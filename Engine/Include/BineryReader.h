#pragma once

JEONG_BEGIN

class JEONG_DLL BineryRead
{
public:
	bool ReadBool();
	int ReadInt();
	float ReadFloat();
	double ReadDouble();

	Vector2 ReadVector2();
	Vector3 ReadVector3();
	Vector4 ReadVector4();
	Matrix ReadMatrix();

	string ReadString();

private:
	HANDLE m_FileHandle;
	DWORD m_Size;

private:
	BineryRead(const string& FileName);
	BineryRead(const wstring& FileName);
	~BineryRead();
};

JEONG_END

