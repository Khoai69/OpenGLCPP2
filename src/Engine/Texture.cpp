#include <vector>
#include <string>
#include "Utils\TGA.h"
#include "Texture.h"

Texture::Texture()
{

}

Texture::~Texture()
{
}
Texture::Texture(const char*  texPath, const char* texName, ETextureFormat format)
{
	m_texName = texName;
	switch (format)
	{
	case ETEXTURE_TGA:
		LoadTexture2D(texPath);
		break;
	default:
		LOG("Texture format is not supported yet!");
		break;
	}
}


void Texture::LoadTexture2D(const char* texName)
{
	char * data = LoadTGA(texName, &m_w, &m_h, &m_bpp);
	if (data)
	{
		glGenTextures(1, &m_texID);

		glBindTexture(GL_TEXTURE_2D, m_texID);

		if (m_bpp == 24)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_w, m_h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_w, m_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);
		delete[] data;
		LOG("[LOADED] Texture 2D <%s> - ID: %d\n", texName, m_texID);
	}
	else
	{
		LOG("\n[ERROR]Cannot create texture %s", texName);
	}

}



CubeTexture::CubeTexture()
{
}

CubeTexture::~CubeTexture()
{
}

CubeTexture::CubeTexture(std::vector<std::string>  texPath, const char* texName, ETextureFormat format)
{
	m_texName = texName;
	glGenTextures(1, &m_texID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texID);
	int width, height, bpp;
	for (int i = 0; i < texPath.size(); i++)
	{
		char * data = LoadTGA(texPath[i].c_str(), &width, &height, &bpp);

		if (data)
		{
			if (bpp == 24)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			}
			delete[] data;
			LOG("[LOADED] Texture CUBE: %s\n", texPath[i].c_str());
		}
		else
		{
			LOG("\n[ERROR]Cannot load texture %s", texPath[i].c_str());
		}
	}


	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	LOG("[Created] Texture CUBE: %d\n", m_texID);
}