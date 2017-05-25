#include "Water.h"
#include "SceneManager.h"
Water::Water()
{
}

Water::~Water()
{
}
extern float delta_time;
void Water::Draw()
{
	PreDraw(); // bind buffers

	ActiveAttribute("a_pos", 3, GL_FLOAT, sizeof(Vertex), NULL);
	ActiveAttribute("a_uv", 2, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
	ActiveAttribute("a_tangent", 3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, tgt));
	ActiveAttribute("a_bitangent", 3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, binorm));
	ActiveAttribute("a_normal", 3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, norm));

	//light pos
	glm::vec3 light_pos = SceneManager::GetInstance()->GetCurrentScene()->GetObjectHaveModelNamed("Bila")->GetPosition();
	GLuint light_pos_location = glGetUniformLocation(GetProgram(), "u_light_pos");
	glUniform3fv(light_pos_location, 1, (GLfloat*)&light_pos);

	//camera pos
	glm::vec3 camPos = SceneManager::GetInstance()->GetCurrentScene()->GetCurrentCamera()->GetCameraPos();
	GLuint camPos_location = glGetUniformLocation(GetProgram(), "u_cameraPos");
	glUniform3fv(camPos_location, 1, (GLfloat*)&camPos);

	//model matrix
	glm::mat4 modelmat = GetModelMatrix();
	GLuint mvp_location = glGetUniformLocation(GetProgram(), "u_model");
	glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (GLfloat*)&modelmat);

	//float time = GetTickCount() / 10000.0f;
	GLint u_time = glGetUniformLocation(m_program, "u_time");
	glUniform1f(u_time, delta_time);

	glDrawElements(GL_TRIANGLES, m_numberIndex, GL_UNSIGNED_SHORT, 0);
	PosDraw(); //unbind buffers
}