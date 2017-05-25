#pragma once
#include <vector>
#include "document.h"
#include "../Engine/Texture.h"
#include "../Engine/ShaderProgram.h"
#include "../Engine/Mesh.h"
#include "filereadstream.h"

class  ResourceManager
{
public:

	 ResourceManager();
	~ ResourceManager();
	static ResourceManager* GetInstance();
	 void LoadResource(const char* res = "resource.json");
	 ShaderProgram* GetProgram(std::string program_name);
	 Texture*  GetTexture(std::string texture_name);
	 Texture*  GetTexture(GLuint id);
	 Mesh* GetMesh(std::string mesh_name);
private:

	static ResourceManager*				s_instance;
	std::vector<Texture*>				m_textures;
	std::vector<ShaderProgram>			m_shaderProgram;
	std::vector<Mesh>					m_mesh;
};
