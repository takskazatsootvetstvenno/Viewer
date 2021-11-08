#include "Model.h"

#include "IndexBuffer.h"
#include "LogManager.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
//#include "UniformBuffer.h"
//#include "ShaderProgram.h"
#include "Texture.h"

#include <assimp/Importer.hpp>
#include <glm/glm.hpp>

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <unordered_map>
#include <vector>
namespace TestEngine {
    struct Vertex {
        glm::fvec3 Position;
        glm::fvec3 Normal;
        glm::fvec2 TexCoord;
    };

   
    /*const std::vector<std::string> Model::getModelTextureNames(unsigned int id) const {
        return m_vData.m_vecTextureNames;
    }*/

    //const VertexBuffer& Model::getBuffer(unsigned int id) const { return m_vData[id].m_VBO; }

    //const IndexBuffer& Model::getIndexBuffer(unsigned int id) const { return m_vData[id].m_EBO; }

    const std::vector<Mesh>& Model::getMeshData() const{
        return m_vData;
    }

    std::vector<Mesh>& Model::getMeshData()
    {
        return m_vData;
    }

   // const unsigned int Model::getBufferNum() const { return m_vData.size(); }

    void processMesh(aiMesh* mesh, std::vector<Vertex>& vertices,
                     std::vector<unsigned int>& indices) {
        // ÷икл по всем вершинам меша
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;
            glm::vec3 vector;  // мы объ€вл€ем промежуточный вектор, т.к. Assimp использует свой
                               // собственный векторный класс, который не преобразуетс€ напр€мую в
                               // тип glm::vec3, поэтому сначала мы передаем данные в этот
                               // промежуточный вектор типа glm::vec3
            //  оординаты
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;

            // Ќормали
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
           
            // “екстурные координаты
            if (mesh->mTextureCoords[0])  // если меш содержит текстурные координаты
            {
                glm::vec2 vec;

                // ¬ершина может содержать до 8 различных текстурных координат. ћы предполагаем, что
                // мы не будем использовать модели, в которых вершина может содержать несколько
                // текстурных координат, поэтому мы всегда берем первый набор (0)
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoord = vec;
            } else
                vertex.TexCoord = glm::vec2(0.0f, 0.0f);
            vertices.push_back(vertex);
        }
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) indices.push_back(face.mIndices[j]);
        }
    }

    Model::Model(const std::string& path,
        std::unordered_map<std::string, Texture>& Textures,
        std::string default_shader_name) 
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
        // ѕроверка на ошибки aiProcess_CalcTangentSpace  aiProcess_PreTransformVertices
        // aiProcess_FlipUVs
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            LogManager::Error() << "[ASSIMP] " << importer.GetErrorString() << LogManager::Show();
            return;
        }

        m_directory = path.substr(0, path.find_last_of('/'));

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;


        for (unsigned int child_id = 0; child_id < scene->mRootNode->mNumChildren; child_id++) {
            for (unsigned int i = 0; i < scene->mRootNode->mChildren[child_id]->mNumMeshes; i++) {
                aiMesh* mesh = scene->mMeshes[scene->mRootNode->mChildren[child_id]->mMeshes[i]];
                std::string mesh_name = mesh->mName.C_Str();
                vertices.clear();
                indices.clear();
                processMesh(mesh, vertices, indices);
                aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
                aiString str;
                material->GetTexture(aiTextureType_DIFFUSE, 0, &str); //only 1 texture
                std::string filename = std::string(str.C_Str());
                std::string filePath = m_directory + '/' + filename;
                Textures.try_emplace(filename, Texture(filePath));

                VertexBuffer tempVBO(
                    &(vertices.front().Position),
                    sizeof(Vertex) * vertices.size(),
                    m_model_buffer_layout);
                IndexBuffer tempEBO(&(indices.front()), indices.size());
                VertexArray tempVAO;
                tempVAO.add_vertex_buffer(tempVBO);
                tempVAO.set_index_buffer(tempEBO);

                m_vData.emplace_back(MeshData(
                    std::move(filename),
                    default_shader_name,
                    std::move(tempVBO),
                    std::move(tempEBO),
                    std::move(tempVAO))
                );
            }
        }
       
    }
}  // namespace TestEngine
