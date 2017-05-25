
#include "gtc/matrix_transform.hpp"
#include "IDrawObject.h"
#include "../Game/ResourceManager.h"

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
		glActiveTexture(GL_TEXTURE0 + texCount);
		if (ResourceManager::GetInstance()->GetTexture(texture)->IsCube())
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, texture);
		}
		
		GLint textureUniform = glGetUniformLocation(m_program, std::string("tex"+ std::to_string(texCount)).c_str());
		glUniform1i(textureUniform, texCount);
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
		LOG("\nCannot find attribute <%s> in program id: <%d>", attribute, m_program);
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
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
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