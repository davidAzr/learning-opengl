#include "model.h"

#include <algorithm>

Model::Model(const char * modelPath)
{
	LoadModel(modelPath);
}

void Model::Draw(Shader shader) const
{
	std::for_each(std::begin(meshes), std::end(meshes), [&shader](const Mesh& mesh) { mesh.Draw(shader); });
}

void Model::LoadModel(std::string path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode * node, const aiScene * scene)
{
	for (auto i = 0; i < node->mNumMeshes; ++i) {
		aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for (auto i = 0; i < node->mNumChildren; ++i) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	Material material;
	
	for (auto i = 0; i < mesh->mNumVertices; ++i) {
		const aiVector3D* vertexAttribute = &(mesh->mVertices[i]);
		
		Vertex vertex;
		
		vertex.Position.x = vertexAttribute->x;
		vertex.Position.y = vertexAttribute->y;
		vertex.Position.z = vertexAttribute->z;

		vertexAttribute = &(mesh->mNormals[i]);
		
		vertex.Normal.x = vertexAttribute->x;
		vertex.Normal.y = vertexAttribute->y;
		vertex.Normal.z = vertexAttribute->z;
		
		if (mesh->HasTextureCoords(0)) {
			vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.TexCoords.x = mesh->mTextureCoords[0][i].y;
		}
		else {
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	for (auto i = 0; i < mesh->mNumFaces; ++i) {
		const aiFace* currentFace = &(mesh->mFaces[i]);
		for (auto t = 0; t < currentFace->mNumIndices; ++t) {
			indices.push_back(currentFace->mIndices[t]);
		}
	}

	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
		//std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		//textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		//std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR , "texture_specular");
		//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		material = processMaterial(mat);
	}

	return Mesh(vertices, indices, textures, material);
}

Material Model::processMaterial(aiMaterial *mat) {
	Material material;
	
	aiColor3D ambient, diffuse, specular;
	float shininess;

	mat->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
	mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
	mat->Get(AI_MATKEY_COLOR_SPECULAR, specular);
	mat->Get(AI_MATKEY_SHININESS, shininess);

	material.ambient.x = ambient.r;
	material.ambient.y = ambient.g;
	material.ambient.z = ambient.b;
	
	material.diffuse.x = diffuse.r;
	material.diffuse.y = diffuse.g;
	material.diffuse.z = diffuse.b;
	
	material.specular.x = specular.r;
	material.specular.y = specular.g;
	material.specular.z = specular.b;
	
	material.shininess = shininess;

	return material;
}
