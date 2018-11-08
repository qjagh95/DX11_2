#pragma once

JEONG_BEGIN

class JEONG_DLL FontManager
{
public:
	bool Init();
	IDWriteTextFormat* FontCreate(const string& KeyName, const TCHAR* FontName, int iWeight, int iStyle, int iStretch, float fSize, const TCHAR* LocalName);
	ID2D1SolidColorBrush* CreateBrush(float r, float g, float b, float a);
	ID2D1SolidColorBrush* CreateBrush(unsigned char r, unsigned char g,	unsigned char b, unsigned char a);
	ID2D1SolidColorBrush* CreateBrush(const Vector4& vColor);

	IDWriteTextFormat* FindFont(const string& KeyName);
	ID2D1SolidColorBrush* FindBrush(float r, float g, float b, float a);
	ID2D1SolidColorBrush* FindBrush(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	ID2D1SolidColorBrush* FindBrush(const Vector4& vColor);

	unsigned int CreateColorKey(float r, float g, float b, float a);
	unsigned int CreateColorKey(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

private:
	IDWriteFactory*	m_WriteFactory;
	unordered_map<string, IDWriteTextFormat*>	m_FontMap;
	unordered_map<unsigned int, ID2D1SolidColorBrush*>	m_BrushMap;

public:
	CLASS_IN_SINGLE(FontManager)
};

JEONG_END