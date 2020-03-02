#ifndef MESH_H
#define	MESH_H

#include <map>
#include <vector>
#include <GL/glew.h>
#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include "glm/glm.hpp"
#include <assimp/cimport.h>
#include "Shader.hpp"

struct Vertex
{
    glm::vec3 pos;
    glm::vec2 tex;
    glm::vec3 normal;

    Vertex() {}

    Vertex(const glm::vec3 _pos, const glm::vec2 _tex, const glm::vec3 _normal)
    {
        pos    = _pos;
        tex    = _tex;
        normal = _normal;
    }
};



class Model
{
public:
    Model();
    ~Model();
    void        Render();
    bool        loadModel(const std::string &Filename);
    void        setTexture(const char *path);
    float       getRadius();

    struct Mesh {
        Mesh();
        ~Mesh();

        void        initBuffers(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices);
        GLuint _vbo_id;
        GLuint _ibo_id;
        unsigned int  _numberOfIndices;
    };

private:

    bool        initFromScene(const aiScene* scene, const std::string& filename);
    void        initMesh(GLuint index, const aiMesh* mesh);
	//bool		InitMaterials(const aiScene* scene, const std::string& filename);
    //void        clear();
    void        printOpenGLError();

   Assimp::Importer         _importer;
   Shader                   _shader;

   std::vector<Mesh>        _mesh_entries;
   GLuint                   _texture;
   GLuint                   _prog;
   GLuint                   _loc;

#define INVALID_MATERIAL 0xFFFFFFFF

};

#endif MESH_H
