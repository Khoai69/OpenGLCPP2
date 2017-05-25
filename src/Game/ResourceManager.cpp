
#include  "ResourceManager.h"

ResourceManager* ResourceManager::s_instance = nullptr;
using namespace rapidjson;

extern std::string GetDataPath();
ResourceManager* ResourceManager::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new ResourceManager();
	}
	return s_instance;
}


ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	for (int i = 0; i < m_textures.size(); i++)
	{
		delete m_textures[i];
		m_textures[i] = nullptr;
	}
}


void ResourceManager::LoadResource(const char* res)
{
	Document document;
	char* content = nullptr;
	//Load text files
	FILE* f = fopen(res, "rb");
	// Determine file size
	fseek(f, 0, SEEK_END);
	size_t size = ftell(f);
	rewind(f);

	content = new char[size];
	rapidjson::FileReadStream is(f, content, size);
	document.ParseStream(is);
	delete[] content;
	fclose(f);

	if (!document.IsNull()) //parse success
	{
		Value& textures = document["Texture"];
		Value& programs = document["Program"];
		Value& models = document["Model"];

		//read texture 
		for (SizeType i = 0; i < textures.Size(); i++)
		{
			Value& texture = textures[i];
			const char*  tex_name = texture["id"].GetString();
			
			const char*  tex_type = texture["type"].GetString();
			Texture* tex;
			if (std::string(tex_type).compare("2d") == 0)
			{
				const char*  tex_path = texture["path"].GetString();
				tex = new Texture((GetDataPath() + tex_path).c_str(), tex_name);
			}
			else if(std::string(tex_type).compare("cubemap") == 0)
			{
				Value& tex_paths = texture["path"];
				std::vector<std::string> paths;
				for (int p = 0; p < tex_paths.Size(); p++)
				{
					std::string path = GetDataPath() + tex_paths[p].GetString();
					paths.push_back(path);
				}
				tex = new CubeTexture(paths, tex_name);

			}
			
			m_textures.push_back(tex);
			//delete tex;
			//tex = nullptr;
		}

		//read shader program 
		for (SizeType i = 0; i < programs.Size(); i++)
		{
			Value& program = programs[i];
			const char* program_name = program["id"].GetString();
			const char* vertex_path = program["Vertex"].GetString();
			const char* fragment_path = program["Fragment"].GetString();
			
			ShaderProgram prg((GetDataPath() + vertex_path).c_str(), (GetDataPath() + fragment_path).c_str(),  program_name);
			m_shaderProgram.push_back(prg);
		}

		//read meshes
		for (SizeType i = 0; i < models.Size(); i++)
		{
			Value& model = models[i];
			const char* model_name = model["id"].GetString();
			const char* model_path = model["path"].GetString();


			Mesh mesh((GetDataPath() + model_path).c_str(),  model_name); //TODO add one more agrument here
			m_mesh.push_back(mesh);
		}
	}
	else
	{
		LOG("\nParse json failed! - ERR %d", document.GetParseError());
	}

}

ShaderProgram* ResourceManager::GetProgram(std::string program_name)
{
	for (int i = 0; i < m_shaderProgram.size(); i++)
	{
		if (m_shaderProgram[i].GetName().compare(program_name) == 0)
		{
			return &m_shaderProgram[i];
		}
	}
	LOG("ERROR: Cannot found program name : %s", program_name.c_str());
	return nullptr;
}

Texture* ResourceManager::GetTexture(std::string texture_name)
{
	for (int i = 0; i < m_textures.size(); i++)
	{
		if (m_textures[i]->GetName().compare(texture_name) == 0)
		{
			return m_textures[i];
		}
	}
	LOG("ERROR: Cannot found texture name : %s", texture_name.c_str());
	return nullptr;
}

Texture*  ResourceManager::GetTexture(GLuint id)
{
	for (int i = 0; i < m_textures.size(); i++)
	{
		if (m_textures[i]->GetID() == id)
		{
			return m_textures[i];
		}
	}
	LOG("ERROR: Cannot found texture id : %d", id);
	return nullptr;
}

Mesh* ResourceManager::GetMesh(std::string mesh_name)
{
	for (int i = 0; i < m_mesh.size(); i++)
	{
		if (m_mesh[i].GetName().compare(mesh_name) == 0)
		{
			return &m_mesh[i];
		}
	}
	LOG("ERROR: Cannot found texture name : %s", mesh_name.c_str());
	return nullptr;
}