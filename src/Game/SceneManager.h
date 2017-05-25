#pragma once

#include <vector>
#include <string>
#include <utility>
#include "Scene.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "../Engine/Camera.h"
class Camera;
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void Init(const char* path);
	void LoadScene(std::string scene_name);
	void Render();
	Scene* GetCurrentScene();
	static SceneManager* GetInstance();
	bool IsInit() { return m_init; }

private:
	static SceneManager* s_instance;
	std::vector<Scene*> m_scenes;
	std::string m_curscene;
	bool m_init;
};

