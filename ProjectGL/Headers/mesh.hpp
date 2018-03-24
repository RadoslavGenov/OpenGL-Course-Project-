//
//  mesh.hpp
//  TestGL
//
//  Created by Radoka on 3/13/18.
//  Copyright © 2018 radoslav.genov.1992. All rights reserved.
//

#ifndef mesh_hpp
#define mesh_hpp

#include "obj_loader.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>

struct Vertex
{
public:
    Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0.0f, 0.0f, 0.0f))
        : pos(pos), texCoord(texCoord), normal(normal) {}
    
    glm::vec3* GetPos() { return &pos; }
    glm::vec2* GetTexCoord() { return &texCoord; }
    glm::vec3* GetNormal() { return &normal; }
    
private:
    glm::vec3 pos;
    glm::vec2 texCoord;
    glm::vec3 normal;
};

enum MeshBufferPositions
{
    POSITION_VB,
    TEXCOORD_VB,
    NORMAL_VB,
    INDEX_VB
};

class Mesh
{
public:
    Mesh(const std::string& fileName);
    Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
    
    void Draw();
    
    virtual ~Mesh();
protected:
private:
    static const unsigned int NUM_BUFFERS = 4;
    void operator=(const Mesh& mesh) {}
    Mesh(const Mesh& mesh) {}
    
    void InitMesh(const IndexedModel& model);
    
    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_numIndices;
};

#endif /* mesh_hpp */
