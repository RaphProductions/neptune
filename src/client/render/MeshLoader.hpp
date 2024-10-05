#pragma once

#include "client/render/Mesh.hpp"
#include <vector>

namespace neptune::client::render {
    class MeshLoader {
    private:
        static void storeData(int attr, int dims, float data[]);
        static void bindIndices(int data[]);
        static int genVAO();

    public:
        static Mesh createMesh(std::vector<float> vertices, std::vector<int> indices);
    };
}