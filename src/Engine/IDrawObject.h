#pragma once
#include <vector>
#include <utility>
#include <string>
#include "Texture.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Utils\ogles_sys.h"
class IDrawObject
{
public:
	IDrawObject();
	~IDrawObject();
	virtual void Draw();
	void PreDraw();
	void PosDraw();
	void UseTextures();
	void UseMeshes();
	void UseProgram();
	void ActiveAttribute(const char* attribute, GLint size, GLenum type, GLsizei stride, GLvoid* ptr);
	void ActiveUniform(const char* uniform);
	void AddTexture(GLuint texID) { m_textures.push_back(texID); }
	void AttachProgram(GLuint programID) { m_program = programID; }
	void AddMesh(std::pair<GLuint, GLuint> meshpair) { m_mesh = meshpair; }
	void SetName(std::string name) { m_name = name; }
	void SetIndices(GLuint idx) { m_numberIndex = idx; }
	glm::vec3 GetPosition() { return m_pos; }
	GLuint GetProgram() { return m_program; }
	std::string GetName() { return m_name; }

	void					SetPos(glm::vec3 pos) { m_pos = pos; }
	void					SetRotate(glm::vec3 rot) { m_rot = rot; }
	void					SetScale(glm::vec3 scale) { m_scale = scale; }
	glm::mat4				GetModelMatrix();


	std::vector<GLuint>				m_textures;
	std::pair<GLuint, GLuint>		m_mesh;
	GLuint							m_numberIndex;
	GLuint							m_program;
	std::string						m_name;

	glm::vec3           m_pos;
	glm::vec3           m_rot;
	glm::vec3			m_scale;

private:

};


