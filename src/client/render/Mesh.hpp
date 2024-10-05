#pragma once

namespace neptune::client::render {
    class Mesh {
    private:
        int vao;
        int ebo;
        int vertices;
    public:
        Mesh(int vao, int ebo, int vertices) :
            vao(vao), ebo(ebo), vertices(vertices) {

        }

        int getVaoID() { return vao; }
        int getEboID() { return ebo; }
        int getVertexCount() { return vertices; }
    };
}