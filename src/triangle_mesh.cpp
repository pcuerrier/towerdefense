#include "triangle_mesh.h"

TriangleMesh::TriangleMesh() {
    
    std::vector<float> positions =
    {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f
    };
    std::vector<int> colorIndices = {
        0, 1, 2, 3
    };
    std::vector<int> elementIndices = {
        0, 1, 2, 2, 1, 3
    };
    vertex_count = 6;

    VBO.resize(2);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(2, VBO.data());
    //position
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, colorIndices.size() * sizeof(int), colorIndices.data(), GL_STATIC_DRAW);

    glVertexAttribIPointer(1, 1, GL_INT, 1 * sizeof(int), (void*)0);
    glEnableVertexAttribArray(1);

    //element buffer
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementIndices.size() * sizeof(int), elementIndices.data(), GL_STATIC_DRAW);
}

void TriangleMesh::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBO.data());
    glDeleteBuffers(1, &EBO);
}