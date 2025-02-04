#include "pch.h"
#include "Converter.h"
#include <filesystem>
#include "Utils.h"
Converter::Converter()
{
	_importer = make_shared<Assimp::Importer>();
}

Converter::~Converter()
{
}

void Converter::ReadAssetFile(wstring file)
{
	wstring fileStr = _assetPath + file;
	auto p = std::filesystem::path(fileStr);
	assert(std::filesystem::exists(p));
	string strPath = string(p.begin(), p.end());
	_scene = _importer->ReadFile(strPath, 
		aiProcess_ConvertToLeftHanded |
		aiProcess_Triangulate |
		aiProcess_GenUVCoords |
		aiProcess_GenNormals |
		aiProcess_CalcTangentSpace
	);

	assert(_scene != nullptr);

}
