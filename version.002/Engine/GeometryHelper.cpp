#include "pch.h"
#include "GeometryHelper.h"

void GeometryHelper::CreateQuad(shared_ptr<Geometry<VertexColorData>> geometry, Color color)
{
	vector<VertexColorData> vertex;
	vertex.resize(4);

	vertex[0].position = { -0.5f, -0.5f, 0.0f };
	vertex[0].color = color;
	vertex[1].position = { -0.5f,  0.5f, 0.0f };
	vertex[1].color = color;
	vertex[2].position = {  0.5f, -0.5f, 0.0f };
	vertex[2].color = color;
	vertex[3].position = {  0.5f,  0.5f, 0.0f };
	vertex[3].color = color;
	geometry->SetVertices(vertex);

	vector<UINT> index = { 0, 1, 2, 2, 1, 3 };
	geometry->SetIndices(index);
}