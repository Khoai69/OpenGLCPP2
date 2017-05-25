#pragma once

#include "Utils\ogles_sys.h"
enum ETextureFormat
{
	ETEXTURE_TGA = 0,
	//TODO: support more format in future
};

class Texture
{
public:

	Texture();
	Texture(const char*  texPath, const char* texName, ETextureFormat format = ETEXTURE_TGA);
	~Texture();

	int					GetWidth() { return m_w; }
	int					GetHeight() { return m_h; }
	int					GetBPP() { return m_bpp; }
	GLuint				GetID() { return m_texID; }
	std::string			GetName() { return m_texName; }
	virtual bool		IsCube() { return false; }
protected:
	//Properties
	int					m_w;
	int					m_h;
	int					m_bpp;
	GLuint				m_texID;
	std::string			m_texName;
	
	void LoadTexture2D(const char* texName);

};

class CubeTexture : public Texture
{
public:
	virtual bool IsCube() { return true; }
	CubeTexture();
	~CubeTexture();
	CubeTexture(std::vector<std::string>  texPath, const char* texName, ETextureFormat format = ETEXTURE_TGA);

private:
	
};


