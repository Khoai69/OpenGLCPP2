#pragma once
#include "glm.hpp"

enum ECameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

// Default camera values
#define YAW			-90.0f
#define PITCH		0.0f
#define SPEED		3.0f
#define SENSITIVTY	0.1f //0.025f
#define ZOOM		45.0f

class Camera
{
public:
	Camera();
	~Camera();
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_speed(SPEED), m_mouseSensitivity(SENSITIVTY), m_zoom(ZOOM)
	{
		m_pos = glm::vec3(posX, posY, posZ);
		m_worldUp = glm::vec3(upX, upY, upZ);
		m_yaw = yaw;
		m_pitch = pitch;
		UpdateCameraVectors();
	}
	void SetCameraNear(float value) { m_near = value; }
	void SetCameraFar(float value) { m_far = value; }
	void SetCameraFOV(float value) { m_fov = value; }
	void SetCameraSpeed(float value) { m_speed = value; }
	void SetCameraPosition(glm::vec3 value) { m_pos = value; }
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	void CameraMove(ECameraMovement direction, GLfloat deltaTime);
	void Zoom(GLfloat yoffset);
	void Rotate(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);

	std::string GetCameraName() { return m_name; }
	void SetCameraName(std::string name) { m_name = name; }
	glm::vec3 GetCameraPos() { return m_pos; }
private:
	float m_near;
	float m_far;
	float m_fov;

	glm::vec3 m_pos;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	// Eular Angles
	GLfloat m_yaw;
	GLfloat m_pitch;
	// Camera options
	GLfloat m_speed;
	GLfloat m_mouseSensitivity;
	GLfloat m_zoom;
	
	std::string m_name;

	void UpdateCameraVectors();
};

