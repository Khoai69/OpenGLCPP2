#include  "Skybox.h"
#include "Fire.h"
#include "Reflection.h"
#include "Phong.h"
#include "Normal.h"
#include "Water.h"
#include "SceneManager.h"

using namespace rapidjson;

SceneManager* SceneManager::s_instance = nullptr;

SceneManager* SceneManager::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new SceneManager();
	}
	return s_instance;
}

SceneManager::SceneManager() : m_init(false)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init(const char* path)
{
	Document document;
	char* content = nullptr;
	//Load text files
	FILE* f = fopen(path, "rb");
	// Determine file size
	fseek(f, 0, SEEK_END);
	size_t size = ftell(f);
	rewind(f);

	content = new char[size];
	rapidjson::FileReadStream is(f, content, size);
	document.ParseStream(is);
	delete[] content;
	fclose(f);
	if (!document.IsNull())
	{
		Scene* pscene = nullptr;
		//travel scene array
		
		
		for (SizeType i = 0; i < document.Size(); i++)
		{
			Value& scene = document[i];
			std::string name = scene["name"].GetString();
			pscene = new Scene();
			pscene->SetName(name);
			//begin add objects
			Value& objects = scene["Objects"];
			int number_of_object = objects.Size();
			for (SizeType obj_idx = 0; obj_idx < objects.Size(); obj_idx++)
			{	
				Value& obj = objects[obj_idx];
				IDrawObject* sceneObj;
				
				std::string program_name = obj["Program"].GetString();
				if (program_name.compare("Generic") == 0)
				{
					sceneObj = new GenericObject();
				}
				else if (program_name.compare("skybox") == 0)
				{
					sceneObj = new Skybox();
				}
				else if (program_name.compare("fire") == 0)
				{
					sceneObj = new Fire();
				}
				else if (program_name.compare("reflection") == 0)
				{
					sceneObj = new Reflection();
				}
				else if (program_name.compare("phong") == 0)
				{
					sceneObj = new Phong();
				}
				else if (program_name.compare("normal") == 0)
				{
					sceneObj = new Normal();
				}
				else if (program_name.compare("water") == 0)
				{
					sceneObj = new Water();
				}
				else //get default
				{
					LOG("Warning: You do not declare handle for shader <%s>, use default shader instead", program_name.c_str());
					sceneObj = new GenericObject();
				}
				//attach shader
				ShaderProgram* program_obj = ResourceManager::GetInstance()->GetProgram(obj["Program"].GetString());
				sceneObj->AttachProgram(program_obj->GetID());
				//add models
				std::string mesh_name = obj["Model"].GetString();
				Mesh* mesh_obj = ResourceManager::GetInstance()->GetMesh(mesh_name);

				//model pos
				Value& pos = obj["Position"];
				Value& rot = obj["Rotation"];
				Value& scale = obj["Scale"];

				glm::vec3 a_pos, a_rot, a_scale;
				for (int p = 0; p < pos.Size(); p++)
				{
					a_pos[p] = pos[p].GetDouble();
				}

				for (int s = 0; s < scale.Size(); s++)
				{
					a_scale[s] = scale[s].GetDouble();
				}

				for (int r = 0; r < rot.Size(); r++)
				{
					a_rot[r] = rot[r].GetDouble();
				}

				sceneObj->SetPos(a_pos);
				sceneObj->SetRotate(a_rot);
				sceneObj->SetScale(a_scale);

				sceneObj->AddMesh(std::make_pair(mesh_obj->GetVertexBufferID(), mesh_obj->GetIndexBufferID()));
				sceneObj->SetIndices(mesh_obj->GetIndices());
				sceneObj->SetName(mesh_name);
				//Add textures
				Value& textures = obj["Texture"];
				for (SizeType tex_idx = 0; tex_idx < textures.Size(); tex_idx++)
				{
					Value& tex = textures[tex_idx];
					std::string tex_name = tex.GetString();
					Texture* tex_obj = ResourceManager::GetInstance()->GetTexture(tex_name);
					sceneObj->AddTexture(tex_obj->GetID());
				}

				pscene->AddObject(sceneObj);
			}
			//Add camera
			Value& cameras = scene["Camera"];
			std::string default_cam;
			for (int c = 0; c < cameras.Size(); c++)
			{
				Camera* cam = new Camera();

				Value& obj_cam = cameras[c];
				std::string cam_name = obj_cam["name"].GetString();
				float cam_near = obj_cam["near"].GetDouble();
				float cam_far = obj_cam["far"].GetDouble();
				float cam_fov = obj_cam["fov"].GetDouble();
				float cam_speed = obj_cam["speed"].GetDouble();
				bool cam_default = obj_cam["default"].GetBool();;

				Value& cam_pos = obj_cam["pos"];
				glm::vec3 pos;
				for (int p = 0; p < cam_pos.Size(); p++)
				{
					pos[p] = cam_pos[p].GetDouble();
				}
				cam->SetCameraFar(cam_far);
				cam->SetCameraNear(cam_near);
				cam->SetCameraFOV(cam_fov);
				cam->SetCameraPosition(pos);
				cam->SetCameraName(cam_name);
				cam->SetCameraSpeed(cam_speed);
				if (cam_default)
					default_cam = cam_name;

				pscene->AddCamera(cam);
			}

			bool is_default = scene["default"].GetBool();
			pscene->SetDefaultCamera(default_cam);
			pscene->InitDone();
			if (pscene->IsInit())
				m_scenes.push_back(pscene);
			if (is_default)
				m_curscene = name;
		}
	}
	else
	{
		LOG("[SceneManager] FAILED to load config file : %s", path);
	}

	m_init = true;
}
void SceneManager::LoadScene(std::string scene_name)
{
	m_curscene = scene_name; //just simple change the name ;}
}
void SceneManager::Render()
{
	GetCurrentScene()->Draw();
}

Scene* SceneManager::GetCurrentScene()
{
	for (auto i : m_scenes)
	{
		if (i->GetName().compare(m_curscene) == 0)
			return i;
	}
	LOG("[SceneManager] ERROR Cannot found any scene");
	return nullptr;
}