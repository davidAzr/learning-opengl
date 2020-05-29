#pragma once

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"

class Model
{
	public:
		Model(const char* modelPath);
		void Draw(Shader shader) const;

	private:
		std::vector<Mesh> meshes;
		std::string directory;

		void LoadModel(std::string path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		Material processMaterial(aiMaterial* material);
};

