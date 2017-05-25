#include "Phong.h"
#include "SceneManager.h"
Phong::Phong()
{
}

Phong::~Phong()
{
}

void Phong::Draw()
{
	PreDraw(); // bind buffers

	ActiveAttribute("a_pos", 3, GL_FLOAT, sizeof(Vertex), NULL);
	ActiveAttribute("a_uv", 2, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));

	//model matrix
	glm::mat4 modelmat = GetModelMatrix();
	GLuint mvp_location = glGetUniformLocation(GetProgram(), "u_model");
	glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (GLfloat*)&modelmat);
	
	//camera pos
	glm::vec3 camPos = SceneManager::GetInstance()->GetCurrentScene()->GetCurrentCamera()->GetCameraPos();
	GLuint camPos_location = glGetUniformLocation(GetProgram(), "u_cameraPos");
	glUniform3fv(camPos_location, 1, (GLfloat*)&camPos);

	//light
	glm::vec3 light_color(1.0f, 1.0f, 1.0f);
	GLuint light_color_location = glGetUniformLocation(GetProgram(), "u_light_color");
	glUniform3fv(light_color_location, 1, (GLfloat*)&light_color);

	glm::vec3 light_pos = SceneManager::GetInstance()->GetCurrentScene()->GetObjectHaveModelNamed("Bila")->GetPosition();
	GLuint light_pos_location = glGetUniformLocation(GetProgram(), "u_light_pos");
	glUniform3fv(light_pos_location, 1, (GLfloat*)&light_pos);

	glDrawElements(GL_TRIANGLES, m_numberIndex, GL_UNSIGNED_SHORT, 0);
	PosDraw(); //unbind buffers
}