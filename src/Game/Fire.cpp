#include "Fire.h"

Fire::Fire()
{
}

Fire::~Fire()
{
}
extern float delta_time;
void Fire::Draw()
{
	PreDraw(); // bind buffers

	ActiveAttribute("a_pos", 3, GL_FLOAT, sizeof(Vertex), NULL);
	ActiveAttribute("a_uv", 2, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
	//float time = GetTickCount() / 1000.0f;
	GLint u_time = glGetUniformLocation(m_program, "u_time");
	glUniform1f(u_time, delta_time);

	//GLint uniformLocation = glGetUniformLocation(m_program, "u_skybox");
	//glUniform1i(uniformLocation, 0);

	glDrawElements(GL_TRIANGLES, m_numberIndex, GL_UNSIGNED_SHORT, 0);
	PosDraw(); //unbind buffers
}