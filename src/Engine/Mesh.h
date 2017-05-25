#pragma once
#include "glm.hpp"
struct Vertex
{
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec3 binorm;
	glm::vec3 tgt;
	glm::vec2 uv;
};

enum EMeshFormat
{
	EMESH_NFG_FORMAT = 0,
	//TODO: support another format in future
};

class Mesh
{
public:
	 Mesh();
	 Mesh(const char* path, EMeshFormat format = EMeshFormat::EMESH_NFG_FORMAT);
	 Mesh(const char* path,const char* name, EMeshFormat format = EMeshFormat::EMESH_NFG_FORMAT);
	~ Mesh();
	
	GLuint					GetVertexBufferID()					{ return m_vertexBufferID; }
	GLuint					GetIndexBufferID()					{ return m_indexBufferID; }
	std::string				GetName()							{ return m_name; }
	GLuint					GetIndices()						{ return m_numberIndices; }

private:

	void				SendToVRAM();
	GLuint				m_vertexBufferID;
	GLuint				m_indexBufferID;
	Vertex*				m_pVertices;
	int					m_numberVertices;
	GLushort*			m_pIndices;
	int					m_numberIndices;
	std::string			m_name;
	void				LoadNFG(const char* path);
};




