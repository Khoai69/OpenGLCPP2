#include "Engine\Utils\ogles_sys.h"
#include "Game\ResourceManager.h"
#include "Game\SceneManager.h"
#include <iostream>
#include <queue>

std::queue<char> g_Keys;
#define MAX_KEYS_PROCESS 10
#define SCREEN_W 1024
#define SCREEN_H 768
#define ZOOM_FACTOR 0.01f
GLfloat g_lastX = 0.0f, g_lastY = 0.0f;
bool g_firstMouse = true;
//begin with bin folder
float delta_time = 0.0f;
std::string GetDataPath()
{
	return "../data/"; //hardcoded
}

void ProcessKey(const char key, float deltaTime)
{
	glm::vec3 curpos;
	switch (key)
	{
	case 'W':
		SceneManager::GetInstance()->GetCurrentScene()->GetCurrentCamera()->CameraMove(ECameraMovement::FORWARD, deltaTime);
		break;
	case 'S':
		SceneManager::GetInstance()->GetCurrentScene()->GetCurrentCamera()->CameraMove(ECameraMovement::BACKWARD, deltaTime);
		break;
	case 'A':
		SceneManager::GetInstance()->GetCurrentScene()->GetCurrentCamera()->CameraMove(ECameraMovement::LEFT, deltaTime);
		break;
	case 'D':
		SceneManager::GetInstance()->GetCurrentScene()->GetCurrentCamera()->CameraMove(ECameraMovement::RIGHT, deltaTime);
		break;
	case 'Q':
		SceneManager::GetInstance()->GetCurrentScene()->GetCurrentCamera()->CameraMove(ECameraMovement::UP, deltaTime);
		break;
	case 'E':
		SceneManager::GetInstance()->GetCurrentScene()->GetCurrentCamera()->CameraMove(ECameraMovement::DOWN, deltaTime);
		break;
	case 'Z':
		SceneManager::GetInstance()->GetCurrentScene()->GetCurrentCamera()->Zoom(ZOOM_FACTOR);
		break;
	case 'X':
		SceneManager::GetInstance()->GetCurrentScene()->GetCurrentCamera()->Zoom(-ZOOM_FACTOR); 
		break;
	case 'J':
		curpos = SceneManager::GetInstance()->GetCurrentScene()->GetObjectHaveModelNamed("Bila")->GetPosition();
		curpos.x += 0.1f;
		SceneManager::GetInstance()->GetCurrentScene()->GetObjectHaveModelNamed("Bila")->SetPos(curpos);
		break;
	case 'L':
		curpos = SceneManager::GetInstance()->GetCurrentScene()->GetObjectHaveModelNamed("Bila")->GetPosition();
		curpos.x -= 0.1f;
		SceneManager::GetInstance()->GetCurrentScene()->GetObjectHaveModelNamed("Bila")->SetPos(curpos);
		break;
	case 'K':
		curpos = SceneManager::GetInstance()->GetCurrentScene()->GetObjectHaveModelNamed("Bila")->GetPosition();
		curpos.y-= 0.1f;
		SceneManager::GetInstance()->GetCurrentScene()->GetObjectHaveModelNamed("Bila")->SetPos(curpos);
		break;

	case 'I':
		curpos = SceneManager::GetInstance()->GetCurrentScene()->GetObjectHaveModelNamed("Bila")->GetPosition();
		curpos.y += 0.1f;
		SceneManager::GetInstance()->GetCurrentScene()->GetObjectHaveModelNamed("Bila")->SetPos(curpos);
		break;
	default:
		break;
	}
	g_Keys.pop();
}

void Render()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	if (SceneManager::GetInstance()->IsInit())
	{
		SceneManager::GetInstance()->Render();
	}
}

void Update(float deltaTime)
{
	//process keys
	for (int i = 0; i< MAX_KEYS_PROCESS; i++)
	{
		if (i >= g_Keys.size())
			break;
		ProcessKey(g_Keys.front(), deltaTime);
	}
	delta_time += deltaTime;
	Sleep(1000 / 60);
}

void Key(unsigned char key, bool bIsPressed)
{
	//std::cout << "Key: "<<key<< " - Keycode:"<< (int)key <<"\n";
	if (bIsPressed)
	{
		g_Keys.push(key);
	}
}

void Init()
{
	ResourceManager::GetInstance()->LoadResource((GetDataPath()+"resources.json").c_str());
	SceneManager::GetInstance()->Init((GetDataPath() + "scenes.json").c_str());
	//SceneManager::GetInstance()->LoadScene("Scene1");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MouseMove(int x, int y)
{
	if (g_firstMouse)
	{
		g_lastX = x;
		g_lastY = y;
		g_firstMouse = false;
	}

	GLfloat xoffset = x - g_lastX;
	GLfloat yoffset = g_lastY - y;  // Reversed since y-coordinates go from bottom to left

	g_lastX = x;
	g_lastY = y;
	SceneManager::GetInstance()->GetCurrentScene()->GetCurrentCamera()->Rotate(xoffset, yoffset);
	if (x < 0 || y < 0 || x > SCREEN_W || y > SCREEN_H) //move out the screen
	{
		g_firstMouse = true;
	}

}

void MouseClickDown(int x, int y)
{

}

void MouseClickUp(int x, int y)
{
	g_firstMouse = true;
}

void main()
{
	SysContext oglSysCtx;
 	ZeroMemory(&oglSysCtx, sizeof(SysContext));

	sysInit(&oglSysCtx, 800, 600);
	Init();
	sysRegisterKeyFunc(&oglSysCtx, Key);
	sysRegisterRenderFunc(&oglSysCtx, Render);
	sysRegisterUpdateFunc(&oglSysCtx, Update);
	sysRegisterMouseDownFunc(&oglSysCtx, MouseClickDown);
	sysRegisterMouseUpFunc(&oglSysCtx, MouseClickUp);
	sysRegisterMouseMoveFunc(&oglSysCtx, MouseMove);

	sysMainLoop(&oglSysCtx);
}

