#include "Reflection.h"
#include "SceneManager.h"
Reflection::Reflection()
{
}

Reflection::~Reflection()
{
}



void Reflection::Draw()
{
	PreDraw(); // bind buffers

	ActiveAttribute("a_pos", 3, GL_FLOAT,sizeof(Vertex),NULL);
	ActiveAttribute("a_normal", 3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, norm));

	//model matrix
	glm::mat4 modelmat = GetModelMatrix();
	GLuint mvp_location = glGetUniformLocation(GetProgram(), "u_model");
	glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (GLfloat*)&modelmat);

	//camera pos
	glm::vec3 camPos = SceneManager::GetInstance()->GetCurrentScene()->GetCurrentCamera()->GetCameraPos();
	GLuint camPos_location = glGetUniformLocation(GetProgram(), "u_cameraPos");
	glUniform3fv(camPos_location, 1, (GLfloat*)&camPos);

	glDrawElements(GL_TRIANGLES, m_numberIndex, GL_UNSIGNED_SHORT, 0);
	PosDraw(); //unbind buffers
}