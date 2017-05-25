#pragma once
#include"GenericObject.h"
#include "../Engine/Camera.h"

class Scene
{
public:
	Scene();
	~Scene();
	void AddObject(IDrawObject* obj) { m_objects.push_back(obj); }
	void AddCamera(Camera* cam) { m_cameras.push_back(cam); }
	void Draw();
	std::string GetName() { return m_name; }
	void SetName(std::string name) { m_name = name; }
	bool IsInit() { return m_inited; }
	void InitDone() { m_inited = true; }
	Camera* GetCurrentCamera();
	void SetDefaultCamera(std::string cam_name);
	IDrawObject* GetObjectHaveModelNamed(std::string obj_name);
private:

	std::vector<IDrawObject*> m_objects;
	std::vector<Camera*> m_cameras;

	Camera* m_currentCam;
	int		CurrentCamID;
	std::string m_name;
	bool m_inited;
};

