struct NFGVertex
{
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec3 binorm;
	glm::vec3 tgt;
	glm::vec2 uv;
};
#define LOGI printf
#define LOGE printf
void LoadNFG(const char* path, NFGVertex* &pVertices, int& nVertices, GLushort* &pIndices, int& nIndices)
{
	////////
	// load NFG file and put it into buffer
	FILE* f = fopen(path, "r");
	if (f == NULL)
	{
		LOGI("Load NFG failed: %s", path);
		return;
	}

	// Read vertices
	fscanf(f, "NrVertices: %d\r\n", &nVertices);
	pVertices = new NFGVertex[nVertices];
	int index = 0;

	for (int i = 0; i < nVertices; i++)
	{
		fscanf(f, "%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\r\n",
			&index,
			&pVertices[i].pos.x,
			&pVertices[i].pos.y,
			&pVertices[i].pos.z,
			&pVertices[i].norm.x,
			&pVertices[i].norm.y,
			&pVertices[i].norm.z,
			&pVertices[i].binorm.x,
			&pVertices[i].binorm.y,
			&pVertices[i].binorm.z,
			&pVertices[i].tgt.x,
			&pVertices[i].tgt.y,
			&pVertices[i].tgt.z,
			&pVertices[i].uv.x,
			&pVertices[i].uv.y
			);
	}

	// read indices
	fscanf(f, "NrIndices: %d\r\n", &nIndices);
	pIndices = new GLushort[nIndices];
	int x, y, z;

	for (int i = 0; i < nIndices; i += 3)
	{
		fscanf(f, "   %d.    %d,    %d,    %d\r\n", &index, &x, &y, &z);
		pIndices[i] = (GLushort)x;
		pIndices[i + 1] = (GLushort)y;
		pIndices[i + 2] = (GLushort)z;
	}

	// clean up
	fclose(f);
	LOGI("[LOADED] Model: %s\n", path);
}