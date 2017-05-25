#include "Normal.h"
#include "SceneManager.h"
Normal::Normal()
{
}

Normal::~Normal()
{
}

void Normal::Draw()
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

	//model matrix
	glm::mat4 modelmat = GetModelMatrix();
	GLuint mvp_location = glGetUniformLocation(GetProgram(), "u_model");
	glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (GLfloat*)&modelmat);

	glDrawElements(GL_TRIANGLES, m_numberIndex, GL_UNSIGNED_SHORT, 0);
	PosDraw(); //unbind buffers
}