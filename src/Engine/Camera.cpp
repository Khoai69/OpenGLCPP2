#include <vector>
#include "gtc/matrix_transform.hpp"
#include "Utils\ogles_sys.h"
#include "Camera.h"

Camera::Camera()
{
	m_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_yaw = YAW;
	m_pitch = PITCH;
	m_front = glm::vec3(0.0f, 0.0f, -1.0f);
	m_speed = SPEED;
	m_mouseSensitivity = SENSITIVTY;
	m_zoom = ZOOM;
	UpdateCameraVectors();
}

Camera::~Camera()
{

}
void Camera::UpdateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

glm::mat4 Camera::GetViewMatrix()
{
	//lookat(pos,target, up);
	return glm::lookAt(m_pos, m_pos + m_front, m_up);
}

glm::mat4 Camera::GetProjectionMatrix()
{
												//width			//height
	return   glm::perspective(m_zoom, (float)800 / (float)600, 0.1f, 1000.0f);//TODO: change screen w/h to variable instead of hardcoded
			//perpective(45degree)
}

void Camera::CameraMove(ECameraMovement direction, GLfloat deltaTime)
{
	GLfloat velocity = m_speed * deltaTime;
	if (direction == FORWARD)
		m_pos += m_front * velocity;
	if (direction == BACKWARD)
		m_pos -= m_front * velocity;
	if (direction == LEFT)
		m_pos -= m_right * velocity;
	if (direction == RIGHT)
		m_pos += m_right * velocity;
	if (direction == UP)
		m_pos += m_up * velocity;
	if (direction == DOWN)
		m_pos -= m_up * velocity;
}

void Camera::Zoom(GLfloat yoffset)
{
	if (m_zoom >= 1.0f && m_zoom <= 45.0f)
		m_zoom -= yoffset;
	if (m_zoom <= 1.0f)
		m_zoom = 1.0f;
	if (m_zoom >= 45.0f)
		m_zoom = 45.0f;
}

void Camera::Rotate(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
	xoffset *= m_mouseSensitivity;
	yoffset *= m_mouseSensitivity;

	m_yaw += xoffset;
	m_pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;
	}
	// Update Front, Right and Up Vectors using the updated Eular angles
	UpdateCameraVectors();
}