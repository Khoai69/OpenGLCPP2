
#include "gtc/matrix_transform.hpp"
#include "IDrawObject.h"

IDrawObject::IDrawObject()
{
}

IDrawObject::~IDrawObject()
{
}

void IDrawObject::UseTextures()
{
	int texCount = 0;
	for (auto texture : m_textures)
	{
		std::string texName ="tex" + std::to_string(texCount);
		GLint textureUniform = glGetUniformLocation(m_program, texName.c_str());
		if (textureUniform >= 0)
		{
			glActiveTexture(GL_TEXTURE0 + texCount);
			glBindTexture(GL_TEXTURE_2D, texture);
			glUniform1i(textureUniform, texCount);
		}
		else
		{
			LOG("\nCannot find texture <%d> in shader <%d>", texture, m_program);
		}
		
		texCount++;
	}	
}

void IDrawObject::ActiveAttribute(const char* attribute, GLint size , GLenum type ,GLsizei stride, GLvoid* ptr)
{
	GLint attr = glGetAttribLocation(m_program, attribute);
	if (attr >= 0)
	{
		glEnableVertexAttribArray(attr);
		glVertexAttribPointer(attr, size, type, GL_FALSE, stride, ptr);
	}
	else
	{
		LOG("\nCannot find attribute <%s> in shader <%d>", attribute, m_program);
	}
}
void IDrawObject::ActiveUniform(const char* uniform)
{

}
void IDrawObject::Draw()
{
	LOG("\n[WARNING] Call draw function from abstract class");
}
void IDrawObject::UseMeshes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_mesh.first);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mesh.second);
}

void IDrawObject::UseProgram()
{
	glUseProgram(m_program);
}

void IDrawObject::PreDraw()
{
	this->UseProgram();
	this->UseTextures();
	this->UseMeshes();
}
void IDrawObject::PosDraw()
{
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	int texCount = 0;
	for (auto texture : m_textures)
	{
		glActiveTexture(GL_TEXTURE0 + texCount);
		glBindTexture(GL_TEXTURE_2D, 0);
		texCount++;
	}
}


glm::mat4 IDrawObject::GetModelMatrix()
{
	glm::mat4 trans;
	glm::mat4 scale;
	glm::mat4 rot;

	trans = glm::translate(trans, m_pos);
	scale = glm::scale(scale, m_scale);

	rot = glm::rotate(rot, glm::radians(m_rot.z), glm::vec3(0.0, 0.0, 1.0));
	rot = glm::rotate(rot, glm::radians(m_rot.x), glm::vec3(1.0, 0.0, 0.0));
	rot = glm::rotate(rot, glm::radians(m_rot.y), glm::vec3(0.0, 1.0, 0.0));
	
	glm::mat4 model = trans * scale * rot;
	return model;
}