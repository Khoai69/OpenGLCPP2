#include "Skybox.h"

Skybox::Skybox()
{
}

Skybox::~Skybox()
{
}


void Skybox::Draw()
{
	PreDraw(); // bind buffers

	ActiveAttribute("a_pos", 3, GL_FLOAT, sizeof(Vertex), NULL);

	glDrawElements(GL_TRIANGLES, m_numberIndex, GL_UNSIGNED_SHORT, 0);
	PosDraw(); //unbind buffers

}