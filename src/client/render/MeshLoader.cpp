#include <client/render/MeshLoader.hpp>
#include <client/glad/glad.h>
#include <vector>

using namespace neptune::client::render;

void MeshLoader::storeData(int attr, int dims, float data[])
{
    int vbo;
    glGenBuffers(1, (GLuint*)&vbo); //Creates a VBO ID

    glBindBuffer(GL_ARRAY_BUFFER, vbo); //Loads the current VBO to store the data
    //FloatBuffer buffer = createFloatBuffer(data);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glVertexAttribPointer(attr, dims, GL_FLOAT, false, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshLoader::bindIndices(int data[])
{
    int vbo;
    glGenBuffers(1, (GLuint*)&vbo);
        //vbos.add(vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
        //IntBuffer buffer = createIntBuffer(data);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}

int MeshLoader::genVAO() {
    int vao;
    glGenVertexArrays(1, (GLuint*)&vao);
        //vaos.add(vao);
    glBindVertexArray(vao);
    return vao;
}

Mesh MeshLoader::createMesh(std::vector<float> vertices, std::vector<int> indices) {

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s), and configure vertex attributes.
    glBindVertexArray(VAO);

    // Bind and set vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size() * 3, vertices.data(), GL_STATIC_DRAW); // Correct size calculation

    // Bind and set index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW); // Correct size calculation

    // Set vertex attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind VBO (safe to unbind since VAO stores the vertex attribute configuration)
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Don't unbind EBO while VAO is still bound, as EBO is stored in the VAO.
    // Unbind VAO (optional)
    glBindVertexArray(0);

    return Mesh(VAO, EBO, indices.size()); // Make sure numIndices is returned correctly
}
