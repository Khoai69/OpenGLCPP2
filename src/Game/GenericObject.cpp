#include "GenericObject.h"

GenericObject::GenericObject()
{
}

GenericObject::~GenericObject()
{
}

void GenericObject::Draw()
{
	PreDraw(); // bind buffers

	ActiveAttribute("a_pos", 3, GL_FLOAT,sizeof(Vertex),NULL);
	ActiveAttribute("a_uv", 2,  GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));

	glDrawElements(GL_TRIANGLES, m_numberIndex, GL_UNSIGNED_SHORT, 0);
	PosDraw(); //unbind buffers
}