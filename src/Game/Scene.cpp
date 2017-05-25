#include "Scene.h"

Scene::Scene() : m_inited(false)
{
}

Scene::~Scene()
{
}

void Scene::Draw()
{
	for (IDrawObject* obj : m_objects)
	{
		glm::mat4 model = obj->GetModelMatrix();
		glm::mat4 projection = GetCurrentCamera()->GetProjectionMatrix();
		glm::mat4 view = GetCurrentCamera()->GetViewMatrix();
		glm::mat4 mvp = projection * view * model;
		glUseProgram(obj->GetProgram());
		GLuint mvp_location = glGetUniformLocation(obj->GetProgram(),"u_mvp");//hard coded
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (GLfloat*)&mvp);
		obj->Draw();
		glUseProgram(0);
	}
}
IDrawObject* Scene::GetObjectHaveModelNamed(std::string obj_name)
{
	for (IDrawObject* obj : m_objects)
	{
		if (obj->GetName().compare(obj_name) == 0)
		{
			return obj;
		}
	}
	LOG("\n[Error] Cannot found object have model named: %s", obj_name.c_str());
	return nullptr;
}
Camera* Scene::GetCurrentCamera()
{
	return m_currentCam;
}

void Scene::SetDefaultCamera(std::string cam_name)
{
	int index = 0;
	for (auto cam : m_cameras)
	{
		if (cam->GetCameraName().compare(cam_name) == 0)
		{
			m_currentCam = cam;
			CurrentCamID = index;
			return;
		}
		index++;
	}
}