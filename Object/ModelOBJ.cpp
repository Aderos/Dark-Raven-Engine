#include "ModelOBJ.h"

ModelOBJ::ModelOBJ()
{
}

ModelOBJ::~ModelOBJ()
{
}

bool ModelOBJ::Load(const char* strModelPath, std::vector<Vector3f>& vVertex, std::vector<Vector2f>& vUV, std::vector<Vector3f>& vNormal)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<Vector3f> temp_vertices;
	std::vector<Vector2f> temp_uvs;
	std::vector<Vector3f> temp_normals;

	// Read file.
	FILE* file = fopen(strModelPath, "r");
	if (file == NULL)
	{
		//cout << "Imposible to open the file!\n" << endl;
		return false;
	}
	while (1)
	{
		char lineHeader[128];

		// Read the first word of the line.
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;

		// Else : parse lineHeader.
		if (strcmp(lineHeader, "v") == 0)
		{
			// Read for vertex.
			Vector3f vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			// Read for uv.
			Vector2f uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			// Read for normal.
			Vector3f normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			// Read for f.
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				//cout << "File can't be read by our simple parser!" << endl;
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else
		{
			// Probably a comment, eat up the rest of the line.
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	// For each vertex of each triangle.
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		// Get the indices of its attributes.
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index.
		Vector3f vertex = temp_vertices[vertexIndex - 1];
		Vector2f uv = temp_uvs[uvIndex - 1];
		Vector3f normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers.
		vVertex.push_back(vertex);
		vUV.push_back(uv);
		vNormal.push_back(normal);
	}

	return true;
}