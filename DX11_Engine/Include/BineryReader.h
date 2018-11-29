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
	string ReadString();
	wstring ReadWString();

private:
	ifstream m_ReadFile;

private:
	BineryRead(const string& FileName);
	BineryRead(const wstring& FileName);
	~BineryRead();
};

JEONG_END

