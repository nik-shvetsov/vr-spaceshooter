//http://ogldev.atspace.co.uk/www/tutorial22/tutorial22.html
#define NOMINMAX
#include "Model.hpp"
#include <algorithm>
#include <iostream>
#include "SOIL.h"

Model::Mesh::Mesh()
{
    _vbo_id = 0;
    _ibo_id = 0;
    _numberOfIndices  = 0;
}

Model::Mesh::~Mesh()
{
}

void Model::Mesh::initBuffers(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices)
{
    _numberOfIndices = indices.size();

    glGenBuffers(1, &_vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glGenBuffers(1, &_ibo_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}
//-----------------------------------MODEL---------------------------------------------------------------------
Model::Model()
{
}

Model::~Model()
{
}

bool Model::loadModel(const std::string& Filename)
{
    bool ret = false;

    const aiScene* _scene = aiImportFile(Filename.c_str(),aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    if (_scene)
        ret = initFromScene(_scene, Filename);
    return ret;
}

bool Model::initFromScene(const aiScene *scene, const std::string &filename) 
{
	_mesh_entries.resize(scene->mNumMeshes);
	for (GLuint i = 0; i < _mesh_entries.size(); i++)
	{
		const aiMesh* mesh = scene->mMeshes[i];
		initMesh(i, mesh);
	}
	return 1;
	//return InitMaterials(scene, filename);
}

void Model::initMesh(GLuint index, const aiMesh *mesh)
{
    _shader.initShaders("shaders/model");
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for (GLuint i = 0 ; i < mesh->mNumVertices ; i++)
    {
        const aiVector3D* pos = &(mesh->mVertices[i]);
        const aiVector3D* normal = &(mesh->mNormals[i]);
        const aiVector3D* texcoord;

        if(mesh->HasTextureCoords(0))
            texcoord = &(mesh->mTextureCoords[0][i]);
        else
            texcoord = &Zero3D;

        Vertex v( glm::vec3( pos->x, pos->y, pos->z), glm::vec2(texcoord->x, texcoord->y), glm::vec3(normal->x, normal->y, normal->z));
        vertices.push_back(v);
    }

    for (GLuint i = 0 ; i < mesh->mNumFaces ; i++)
    {
        const aiFace& face = mesh->mFaces[i];
        assert(face.mNumIndices == 3);
        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);
    }

    _mesh_entries[index].initBuffers(vertices, indices);
}

void Model::Render()
{
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texture);


    _loc = glGetUniformLocation(_prog,"texture0");
    glUniform1i(_loc, 0);

    for (GLuint i = 0 ; i < _mesh_entries.size() ; i++)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _mesh_entries[i]._vbo_id);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(Vertex), 0);

        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex),(const GLvoid*)(sizeof(glm::vec3)));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mesh_entries[i]._ibo_id);
        glDrawElements(GL_TRIANGLES, _mesh_entries[i]._numberOfIndices, GL_UNSIGNED_INT, (const GLvoid*)0x0);
    }

    glBindTexture(GL_TEXTURE_2D,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Model::setTexture(const char* path)
{
    _texture = SOIL_load_OGL_texture(
        path,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if( 0 == _texture)
    {
        std::cout<<"Error: "<<SOIL_last_result();
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // Set environment mode
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture( GL_TEXTURE_2D, 0x0 );
}

float Model::getRadius()
{
    aiVector3D scene_min, scene_max, scene_center;
    //get_bounding_box(&scene_min,&scene_max);
    scene_center.x = (scene_min.x + scene_max.x) / 2.0f;
    scene_center.y = (scene_min.y + scene_max.y) / 2.0f;
    scene_center.z = (scene_min.z + scene_max.z) / 2.0f;
    float x = std::abs(scene_max.x - scene_min.x );
    float y = std::abs(scene_max.y - scene_min.y );
    float z = std::abs(scene_max.z - scene_min.z );

    float r = std::max(x,y);
    r = std::max(r, z);
    return  r/2.0f;
}

void Model::printOpenGLError()
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
        std::cout << "OpenGL error in model: " << err;
}
