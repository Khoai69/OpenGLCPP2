#include "Utils\ogles_sys.h"
#include <stdio.h>
#include <string>
#include "gtc/matrix_transform.hpp"
#include "Mesh.h"

Mesh::Mesh()
{

}
Mesh::Mesh(const char* path, const char* name, EMeshFormat format)
{
	m_name = name;
	switch (format)
	{
	case EMeshFormat::EMESH_NFG_FORMAT:
		LoadNFG(path);
		break;
	default:
		LOG("File format is not support yet!");
	};
	
}
Mesh::Mesh(const char* path, EMeshFormat format)
{
	switch (format)
	{
	case EMeshFormat::EMESH_NFG_FORMAT:
		LoadNFG(path);
		break;
	default:
		LOG("File format is not support yet!");
	};
}
Mesh::~Mesh()
{
	//delete m_pIndices;
	//delete m_pVertices;
}
void Mesh::SendToVRAM()
{
	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, m_numberVertices * sizeof(Vertex), m_pVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numberIndices * sizeof(GLushort), m_pIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] m_pIndices;
	delete[] m_pVertices;
	m_pIndices = nullptr;
	m_pVertices = nullptr;
}
void Mesh::LoadNFG(const char* path)
{
	////////
	// load NFG file and put it into buffer
	FILE* f = fopen(path, "r");
	if (f == NULL)
	{
		LOG("Load NFG failed: %s", path);
		return;
	}

	// Read vertices
	fscanf(f, "NrVertices: %d\r\n", &m_numberVertices);
	m_pVertices = new Vertex[m_numberVertices];
	int index = 0;

	for (int i = 0; i < m_numberVertices; i++)
	{
		fscanf(f, "%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\r\n",
			&index,
			&m_pVertices[i].pos.x,
			&m_pVertices[i].pos.y,
			&m_pVertices[i].pos.z,
			&m_pVertices[i].norm.x,
			&m_pVertices[i].norm.y,
			&m_pVertices[i].norm.z,
			&m_pVertices[i].binorm.x,
			&m_pVertices[i].binorm.y,
			&m_pVertices[i].binorm.z,
			&m_pVertices[i].tgt.x,
			&m_pVertices[i].tgt.y,
			&m_pVertices[i].tgt.z,
			&m_pVertices[i].uv.x,
			&m_pVertices[i].uv.y
		);
	}

	// read indices
	fscanf(f, "NrIndices: %d\r\n", &m_numberIndices);
	m_pIndices = new GLushort[m_numberIndices];
	int x, y, z;

	for (int i = 0; i < m_numberIndices; i += 3)
	{
		fscanf(f, "   %d.    %d,    %d,    %d\r\n", &index, &x, &y, &z);
		m_pIndices[i] = (GLushort)x;
		m_pIndices[i + 1] = (GLushort)y;
		m_pIndices[i + 2] = (GLushort)z;
	}

	// clean up
	fclose(f);
	LOG("\n[LOADED] Model: %s", path);
	SendToVRAM();
}

