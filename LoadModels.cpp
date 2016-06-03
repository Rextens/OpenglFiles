#include "loadModels.h"



LoadModels::LoadModels(std::string file_name, Vectors &vectors)
{
	const aiScene* scene = aiImportFile(file_name.c_str(), aiProcess_Triangulate);
	if (!scene)
	{
		std::cout << "Mesh not found." << std::endl;
		return;
	}

	int total_vertices_count = 0;

	std::vector<GLfloat> buffer_vbo_data;

	for (int i = 0; i != scene->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[i];

		int mesh_vertices = 0;

		for (int j = 0; j != mesh->mNumFaces; j++)
		{
			const aiFace* face = &mesh->mFaces[j];

			for (int k = 0; k != 3; k++)
			{
				aiVector3D vertex_position{ 0, 0, 0 };
				aiVector3D vertex_normal{ 0, 0, 0 };
				aiVector3D vertex_texture_coord{ 0, 0, 0 };

				if (mesh->HasPositions())
					vertex_position = mesh->mVertices[face->mIndices[k]];

				if (mesh->HasNormals())
					vertex_normal = mesh->mNormals[face->mIndices[k]];

				if (mesh->HasTextureCoords(0))
					vertex_texture_coord = mesh->mTextureCoords[0][face->mIndices[k]];

				buffer_vbo_data.push_back(vertex_position.x);
				buffer_vbo_data.push_back(vertex_position.y);
				buffer_vbo_data.push_back(vertex_position.z);

				buffer_vbo_data.push_back(vertex_normal.x);
				buffer_vbo_data.push_back(vertex_normal.y);
				buffer_vbo_data.push_back(vertex_normal.z);

				buffer_vbo_data.push_back(vertex_texture_coord.x);
				buffer_vbo_data.push_back(vertex_texture_coord.y);

				mesh_vertices++;
			}
		}

		vectors.mesh_vertices_count.push_back(mesh_vertices);
		vectors.mesh_starting_vertex_index.push_back(total_vertices_count);
		total_vertices_count += mesh_vertices;

		if (scene->mNumMaterials != 0)
		{
			const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			aiString texture_path;

			GLuint tex = 0;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texture_path) ==
				AI_SUCCESS)
			{
				unsigned int found_pos = file_name.find_last_of("/\\");
				std::string path = file_name.substr(0, found_pos);
				std::string name(texture_path.C_Str());
				if (name[0] == '/')
					name.erase(0, 1);

				std::string file_path = path + "/" + name;


				if (render.loadTexture(file_path, tex))
					std::cout << "Texture " << file_path << " not found." <<
					std::endl;
				else
					std::cout << "Texture " << file_path << " loaded." <<
					std::endl;
			}

			vectors.textures.push_back(tex);
		}
	}

	GLuint vbo_buffer = 0;
	glGenBuffers(1, &vbo_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_buffer);
	glBufferData(GL_ARRAY_BUFFER, buffer_vbo_data.size() * sizeof(GLfloat),
		buffer_vbo_data.data(), GL_STATIC_DRAW);

	int single_vertex_size = 2 * 3 * sizeof(GLfloat) + 2 * sizeof(GLfloat);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, single_vertex_size, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, single_vertex_size,
		reinterpret_cast<void*>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, single_vertex_size,
		reinterpret_cast<void*>(2 * 3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}
LoadModels::~LoadModels()
{

}
void LoadModels::drawModel(GLint textureSlot, Vectors &vectors)
{
	glBindVertexArray(vao);
	for (int i = 0; i < vectors.mesh_starting_vertex_index.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, vectors.textures[i]);
		glUniform1i(textureSlot, 1);
		glDrawArrays(GL_TRIANGLES, vectors.mesh_starting_vertex_index[i], vectors.mesh_vertices_count[i]);
	}
}
